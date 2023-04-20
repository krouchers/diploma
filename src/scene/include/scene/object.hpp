#pragma once

#include "mesh.hpp"

namespace scene
{
    class Object
    {
    public:
        void Render(const Mat4x4 &view);

    private:
        gl::Mesh mesh_;
    };
}