#include "object.hpp"
#include "renderer.hpp"

using namespace scene;
void Object::Render(const Mat4x4 &view)
{
    Renderer::Get().Mesh(mesh_, view);
}