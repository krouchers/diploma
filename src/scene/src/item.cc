#include "scene/item.hpp"
#include "scene/renderer.hpp"

#include "glm/mat4x4.hpp"

namespace scene
{
    Item::Item(geometry::HalfedgeMesh &&mesh)
        : halfedge_mesh_{std::move(mesh)}, mesh_{}
    {
        SyncMesh();
    }

    void Item::Render(const glm::mat4x4 &view)
    {
        Renderer::Get().Mesh(mesh_, view);
    }

    Item::Item(Item &&src)
        : halfedge_mesh_{std::move(src.halfedge_mesh_)},
          mesh_{std::move(src.mesh_)}
    {
    }

    void Item::SyncMesh()
    {
        mesh_ = halfedge_mesh_.ToMesh();
        mesh_dirty = false;
    }
}