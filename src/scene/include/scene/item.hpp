#pragma once

#include "object.hpp"
#include "mesh.hpp"
#include "glm/mat4x4.hpp"

namespace scene
{
    class Item
    {
    public:
        Item(const gl::Mesh &mesh);
        void Render(const glm::mat4x4 &view);

    private:
        gl::Mesh mesh_;
    };
}