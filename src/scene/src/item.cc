#include "scene/item.hpp"
#include "scene/renderer.hpp"

#include "glm/mat4x4.hpp"

namespace scene
{
    Item::Item(const gl::Mesh &mesh)
        : mesh_{std::move(mesh)}
    {
    }

    void Item::Render(const glm::mat4x4 &view)
    {
        Renderer::Get().Mesh(mesh_, view);
    }

}