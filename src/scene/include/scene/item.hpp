#pragma once

#include "definitions.hpp"
#include "object.hpp"
#include "geometry/mesh.hpp"
#include "glm/mat4x4.hpp"
#include "geometry/halfedge_mesh.hpp"

namespace scene
{
    class GEODIP_API Item
    {
    public:
        Item(geometry::HalfedgeMesh &&mesh);
        Item(Item &&item);

        void Render(const glm::mat4x4 &view);


    private:
        void SyncMesh();
        geometry::HalfedgeMesh halfedge_mesh_;
        gl::Mesh mesh_;

        bool mesh_dirty = true;
    };
}