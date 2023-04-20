#pragma once

#include "object.hpp"
#include "mesh.hpp"

namespace scene
{
    class Item
    {
    public:
        Item(const gl::Mesh &mesh);
        void Render(const Mat4x4 &view);

    private:
        gl::Mesh mesh_;
    };
}