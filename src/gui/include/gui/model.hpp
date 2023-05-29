#pragma once

#include "gui/widgets.hpp"
#include "scene/scene.hpp"

#include "opengl/instance.hpp"

#include "geometry/halfedge_mesh.hpp"

namespace gui
{
    class Model
    {
    public:
        Model();
        void Render(MayBeItem obj_opt, Widgets &widgets);

        std::tuple<geometry::Mesh &, gl::Instance &> Shapes();

        void SetHoverID(SceneID id);
        void Select(SceneID id, Widgets &widgets, const glm::vec3 &click_dir, const glm::vec3 &cam_pos);
        SceneID GetHoverID();
        glm::vec3 GetSelectedPos();

        void ApplyTransform(Widgets &Widgets);

    private:
        void VertVisualize(geometry::HalfedgeMesh::VertexRef v);
        void UpdateVertex(geometry::HalfedgeMesh::VertexRef v);
        void SetupMeshComponents(scene::Item &item);
        std::pair<std::vector<geometry::Mesh::Vert>,
                  std::vector<geometry::Mesh::Index>>
        ExtractVertsAndIndexes();
        std::optional<geometry::HalfedgeMesh::ElementRef> GetSelectedElem();
        glm::mat4x4 GetTransformForSphere(geometry::HalfedgeMesh::VertexRef v);

        glm::vec3 mesh_color_{1.0f, 1.0f, 1.0f};

        geometry::HalfedgeMesh *halfedge_mesh_;

        geometry::Mesh face_mesh_;
        gl::Instance spheres_;

        SceneID hovered_id_, selected_id_;

        struct TransformData
        {
            glm::vec3 center_;
        } old_data_;

        struct Info
        {
            geometry::HalfedgeMesh::ElementRef element_;
            size_t instance_id;
        };

        std::unordered_map<SceneID, Info> id_to_info_;
    };
}