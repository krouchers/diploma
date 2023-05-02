#pragma once

#include "glm/mat4x4.hpp"

#include "definitions.hpp"
#include "object.hpp"

#include "geometry/mesh.hpp"
#include "geometry/halfedge_mesh.hpp"

#include "scene/pose.hpp"

namespace scene
{
    class GEODIP_API Item
    {
    public:
        Item(geometry::HalfedgeMesh &&mesh);
        Item(Item &&item);

    void Render(bool posed, const glm::mat4x4 &view);

    private:
        void SyncMesh();

        geometry::HalfedgeMesh halfedge_mesh_;
        gl::Mesh mesh_;

        Pose pose_;
        bool mesh_dirty = true;
    };
}