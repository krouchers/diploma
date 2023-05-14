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

    private:
        void VertVisualize(geometry::HalfedgeMesh::VertexRef v);
        void SetupMeshComponents(scene::Item &item);
        void ExtractVertsAndIndexes(geometry::HalfedgeMesh::FaceRef f,
                                    std::vector<geometry::Mesh::Vert> &verts,
                                    std::vector<geometry::Mesh::Index> &inds,
                                    size_t extract_at);

        glm::vec3 mesh_color_{1.0f, 1.0f, 1.0f};

        geometry::HalfedgeMesh *halfedge_mesh_;
        geometry::Mesh face_mesh_;

        gl::Instance spheres_;
    };
}