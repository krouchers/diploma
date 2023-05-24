#include "gui/model.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/transform.hpp"

#include "scene/renderer.hpp"

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

        face_mesh_.Recreate(std::move(verts), std::move(inds));

        // vertices visualization
        spheres_.Clear();
        for (auto v = halfedge_mesh_->VerticesBegin(); v != halfedge_mesh_->VerticesEnd(); ++v)
        {
            spheres_.Add(GetTransformForSphere(v), v->id_);
            id_to_info_[v->id_].element_ = v;
        }
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
    void Model::Select(SceneID id)
    {
        selected_id_ = id;
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
}