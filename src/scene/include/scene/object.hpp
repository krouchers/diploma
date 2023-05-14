#pragma once

#include "definitions.hpp"
#include "geometry/mesh.hpp"
#include "glm/mat4x4.hpp"

namespace scene
{
    class GEODIP_API Object
    {
    public:
        void Render(const glm::mat4x4 &view);

    private:
        geometry::Mesh mesh_;
    };
}