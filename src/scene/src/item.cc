#include "scene/item.hpp"
#include "scene/renderer.hpp"

#include "glm/mat4x4.hpp"

namespace scene
{
    Item::Item(SceneID id, geometry::HalfedgeMesh &&mesh)
        : id_{id}, halfedge_mesh_{std::move(mesh)}, mesh_{}
    {
        SyncMesh();
    }

    void Item::Render(const glm::mat4x4 &view)
    {
        scene::Renderer::Opts opts;
        opts.model_view_ = view * pose_.Transform();
        opts.color_ = {0.0f, 1.0f, 0.0f};
        opts.id_ = id_;
        Renderer::Get().Mesh(mesh_, opts);
    }

    Item::Item(Item &&src)
        : id_{src.id_},
          halfedge_mesh_{std::move(src.halfedge_mesh_)},
          mesh_{std::move(src.mesh_)}

    {
    }

    void Item::SyncMesh()
    {
        mesh_ = halfedge_mesh_.ToMesh();
        mesh_dirty = false;
    }

    Item::Item(SceneID id, Pose pose, utils::Data &&meshData)
        : pose_{pose}, id_{id}, halfedge_mesh_{std::move(meshData)}, mesh_{}
    {
        SyncMesh();
    }
}