#pragma once

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "geometry/line.hpp"

namespace geometry
{
    struct Plane
    {
        glm::vec3 pos_;
        glm::vec3 norm_;

        glm::vec3 hit(const Line &line)
        {
            float t = -(glm::dot(norm_, line.pos_) - glm::dot(norm_, pos_)) / glm::dot(norm_, line.dir_);
            return line.At(t);
        }
    };
}