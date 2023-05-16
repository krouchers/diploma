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
        (void)widgets;
    }

    void Model::SetupMeshComponents(scene::Item &item)
    {
        geometry::HalfedgeMesh *old = halfedge_mesh_;
        halfedge_mesh_ = item.GetHalfedgeMesh();
        if (old == halfedge_mesh_)
        {
            return;
        }

        using Vert = geometry::Mesh::Vert;
        using Index = geometry::Mesh::Index;

        std::vector<Vert> verts;
        std::vector<Index> inds;

        // faces visualization
        for (auto faces_begin = halfedge_mesh_->FacesBegin(); faces_begin != halfedge_mesh_->FacesEnd(); ++faces_begin)
            ExtractVertsAndIndexes(faces_begin, verts, inds, verts.size());

        face_mesh_.Recreate(std::move(verts), std::move(inds));

        // vertices visualization
        spheres_.Clear();
        for (auto v = halfedge_mesh_->VerticesBegin(); v != halfedge_mesh_->VerticesEnd(); ++v)
        {
            spheres_.Add(GetTransformForSphere(v), v->id_);
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

    void Model::ExtractVertsAndIndexes(geometry::HalfedgeMesh::FaceRef f,
                                       std::vector<geometry::Mesh::Vert> &verts,
                                       std::vector<geometry::Mesh::Index> &inds,
                                       size_t extract_at)
    {
        auto h = f->halfedge_;
        auto i = h;
        auto id = f->id_;

        std::vector<glm::vec3> face_vert_positions;
        do
        {
            face_vert_positions.push_back(i->vertex_->pos_);
            i = i->next_;
        } while (i != h);

        size_t augment_size = extract_at + 3;
        if (verts.size() < augment_size)
            verts.resize(augment_size);
        if (inds.size() < augment_size)
            inds.resize(augment_size);

        auto v0 = face_vert_positions[0];
        auto v1 = face_vert_positions[1];
        auto v2 = face_vert_positions[2];

        auto n = glm::normalize(glm::cross(v1 - v0, v2 - v0));

        verts[extract_at] = {v0, n, id};
        inds[extract_at++] = extract_at;

        verts[extract_at] = {v1, n, id};
        inds[extract_at++] = extract_at;

        verts[extract_at] = {v2, n, id};
        inds[extract_at++] = extract_at;
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
    void Model::SetSelectID(SceneID id)
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
}