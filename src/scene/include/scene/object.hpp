#pragma once

#include "mesh.hpp"
#include "glm/mat4x4.hpp"

namespace scene
{
    class Object
    {
    public:
        void Render(const glm::mat4x4 &view);

    private:
        gl::Mesh mesh_;
    };
}