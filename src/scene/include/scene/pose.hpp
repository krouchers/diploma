#pragma once
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

#include "math/quat.hpp"
#include "common/definitions.hpp"

namespace scene
{
    struct GEODIP_API Pose
    {
        glm::mat4x4 Transform() const;

        static Pose Rotated(const glm::vec3 &euler)
        {
            return Pose{euler, {}};
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