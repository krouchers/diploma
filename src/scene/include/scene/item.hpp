#pragma once

#include "definitions.hpp"
#include "object.hpp"
#include "geometry/mesh.hpp"
#include "glm/mat4x4.hpp"

namespace scene
{
    class GEODIP_API Item
    {
    public:
        Item(const gl::Mesh &mesh);
        void Render(const glm::mat4x4 &view);

    private:
        gl::Mesh mesh_;
    };
}