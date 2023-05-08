#pragma once

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace geometry
{
    struct Line
    {
        glm::vec3 pos_;
        glm::vec3 dir_;

        glm::vec3 At(float t) const
        {
            return pos_ + t * dir_;
        };

        glm::vec3 ClosestTo(glm::vec3 p)
        {
            float t = glm::dot((p - pos_), dir_);
            return At(t);
        }
    };
}