#pragma once

#include "glm/mat4x4.hpp"
#include "common/colors.hpp"

#include "definitions.hpp"
#include "object.hpp"

#include "geometry/mesh.hpp"
#include "geometry/halfedge_mesh.hpp"

#include "scene/pose.hpp"

using SceneID = unsigned int;

namespace scene
{
    class GEODIP_API Item
    {
    public:
        Item(SceneID id, geometry::HalfedgeMesh &&mesh);
        Item(SceneID id, Pose pose, geometry::HalfedgeMesh &&mesh);
        Item(SceneID id, Pose pose, utils::Data &&meshData);
        Item(Item &&item);

        void Render();

        Pose pose_;
        glm::vec3 color_{Color::white};

    private:
        void SyncMesh();

        SceneID id_;
        geometry::HalfedgeMesh halfedge_mesh_;
        gl::Mesh mesh_;

        bool mesh_dirty = true;
    };
}