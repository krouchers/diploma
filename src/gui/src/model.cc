#include "gui/model.hpp"

#include "glm/vec3.hpp"
#include "glm/gtx/transform.hpp"

#include "scene/renderer.hpp"

#include "common/overloaded.hpp"

#include <variant>

namespace gui
{
    void Model::Render(MayBeItem obj_opt, Widgets &widgets)
    {
        if (obj_opt)
            SetupMeshComponents(obj_opt.value());

        auto &r = scene::Renderer::Get();
        scene::Renderer::HalfedgeOpts opts(Shapes());
        opts.hov_id_ = hovered_id_;
        opts.sel_id_ = selected_id_;
        r.Halfedge(opts);

        auto elem = GetSelectedElem();
        if (elem)
        {
            auto pos = geometry::HalfedgeMesh::CenterOf(elem.value());
            widgets.Render(pos, 1.0f);
        }
    }

    void Model::SetupMeshComponents(scene::Item &item)
    {
        geometry::HalfedgeMesh *old = halfedge_mesh_;
        halfedge_mesh_ = item.GetHalfedgeMesh();
        if (old == halfedge_mesh_)
        {
            return;
        }

        // faces visualization
        auto [verts, inds] = ExtractVertsAndIndexes();

        face_mesh_.Recreate({std::move(verts), std::move(inds)});

        // vertices visualization
        spheres_.Clear();
        for (auto v = halfedge_mesh_->VerticesBegin(); v != halfedge_mesh_->VerticesEnd(); ++v)
            id_to_info_[v->id_] = {v, spheres_.Add(GetTransformForSphere(v), v->id_)};
    }

    Model::Model()
        : spheres_{geometry::Mesh{utils::GenerateSphere(1.0f, 2)}}
    {
    }

    void Model::VertVisualize(geometry::HalfedgeMesh::VertexRef v)
    {
        glm::mat4x4 transform{
            glm::vec4{glm::vec3{1.0f, 0.0f, 0.0f}, 0.0f},
            glm::vec4{glm::vec3{0.0f, 1.0f, 0.0f}, 0.0f},
            glm::vec4{glm::vec3{0.0f, 0.0f, 1.0f}, 0.0f},
            glm::vec4{v->pos_, 0.0f}};
        spheres_.Add(transform, v->id_);
    }

    void Model::UpdateVertex(geometry::HalfedgeMesh::VertexRef v)
    {
        spheres_.Get(id_to_info_[v->id_].instance_id).transform_[3] = {v->pos_, 1.0f};
        auto [verts, inds] = ExtractVertsAndIndexes();
        face_mesh_.Recreate({std::move(verts), std::move(inds)});
    }

    std::pair<std::vector<geometry::Mesh::Vert>,
              std::vector<geometry::Mesh::Index>>
    Model::ExtractVertsAndIndexes()
    {
        using Vert = geometry::Mesh::Vert;
        using Index = geometry::Mesh::Index;
        std::vector<Vert> mesh_verts;
        std::vector<Index> mesh_inds;
        for (auto f = halfedge_mesh_->FacesBegin(); f != halfedge_mesh_->FacesEnd(); ++f)
        {
            auto h = f->halfedge_;
            auto i = h;
            auto id = f->id_;
            std::vector<glm::vec3> face_verts;
            do
            {
                face_verts.push_back(i->vertex_->pos_);
                i = i->next_;
            } while (i != h);

            auto v0 = face_verts[0];
            auto v1 = face_verts[1];
            auto v2 = face_verts[2];
            auto n = glm::normalize(glm::cross(v1 - v0, v2 - v0));

            mesh_inds.push_back(mesh_verts.size());
            mesh_verts.push_back({v0, n, id});

            mesh_inds.push_back(mesh_verts.size());
            mesh_verts.push_back({v1, n, id});

            mesh_inds.push_back(mesh_verts.size());
            mesh_verts.push_back({v2, n, id});
        }
        return {mesh_verts, mesh_inds};
    }

    std::tuple<geometry::Mesh &, gl::Instance &> Model::Shapes()
    {
        return {face_mesh_, spheres_};
    }

    void Model::SetHoverID(SceneID id)
    {
        hovered_id_ = id;
    }

    SceneID Model::GetHoverID()
    {
        return hovered_id_;
    }
    void Model::Select(SceneID id, Widgets &widgets, const glm::vec3 &click_dir, const glm::vec3 &cam_pos)
    {
        if (id >= (SceneID)WidgetsIds::count)
            selected_id_ = id;
        if (widgets.dragging_)
        {
            auto e = GetSelectedElem().value();
            old_data_.center_ = geometry::HalfedgeMesh::CenterOf(e);
            widgets.StartDrag(
                geometry::HalfedgeMesh::CenterOf(e),
                click_dir,
                cam_pos);
        }
    }

    glm::mat4x4 Model::GetTransformForSphere(geometry::HalfedgeMesh::VertexRef v)
    {
        return {
            glm::vec4{0.25f, 0.0f, 0.0f, 0.0f},
            glm::vec4{0.0f, 0.25f, 0.0f, 0.0f},
            glm::vec4{0.0f, 0.0f, 0.25f, 0.0f},
            glm::vec4{v->pos_, 1.0f},
        };
    }

    std::optional<geometry::HalfedgeMesh::ElementRef> Model::GetSelectedElem()
    {
        auto entry = id_to_info_.find(selected_id_);
        if (entry == id_to_info_.end())
        {
            return std::nullopt;
        }
        return entry->second.element_;
    }
    glm::vec3 Model::GetSelectedPos()
    {
        return geometry::HalfedgeMesh::CenterOf(GetSelectedElem().value());
    }

    void Model::ApplyTransform(Widgets &widgets)
    {
        auto elem = GetSelectedElem().value();
        auto delta = widgets.ApplyTransform({});
        auto abs_pos = old_data_.center_ + delta.pos_;
        std::visit(overloaded{[&](geometry::HalfedgeMesh::VertexRef v)
                              {
                                  v->pos_ = abs_pos;
                                  UpdateVertex(v);
                              },
                              [&](geometry::HalfedgeMesh::EdgeRef e)
                              {
                                  (void)e;
                              },
                              [&](geometry::HalfedgeMesh::FaceRef f)
                              {
                                  (void)f;
                              },
                              [&](geometry::HalfedgeMesh::HalfedgeRef h)
                              {
                                  (void)h;
                              }},
                   elem);
    }

    void Model::EndTransform(MayBeItem item, Model &model)
    {
        item.value().get().UpdateHalfedgeMesh(*model.halfedge_mesh_);
    }
}