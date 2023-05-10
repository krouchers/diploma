#pragma once
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

#include "math/quat.hpp"

namespace scene
{
    struct Pose
    {
        glm::mat4x4 Transform() const;

        static Pose Rotated(const glm::vec3 &euler)
        {
            return Pose{euler, {}, {1.0f, 1.0f, 1.0f}};
        }

        math::Quat RotationQuat() const
        {
            return math::Quat::euler(euler_);
        }

        glm::vec3 euler_{};
        glm::vec3 pos_{};
        glm::vec3 scale_{1, 1, 1};
    };
}