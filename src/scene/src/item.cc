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

    void Item::Render(bool posed, const glm::mat4x4 &view)
    {
        scene::Renderer::Opts opts;
        opts.model_view_ = posed ? view * pose_.transform() : view;
        opts.color_ = {0.0f, 1.0f, 0.0f};
        Renderer::Get().Mesh(mesh_, opts);
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