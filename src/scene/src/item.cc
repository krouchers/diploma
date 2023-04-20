#include "scene/item.hpp"
#include "scene/renderer.hpp"

namespace scene
{
    Item::Item(const gl::Mesh &mesh)
        : mesh_{std::move(mesh)}
    {
    }

    void Item::Render(const Mat4x4 &view)
    {
        Renderer::Get().Mesh(mesh_, view);
    }

}