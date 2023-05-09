#include "scene/pose.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace scene
{
    glm::mat4x4 Pose::Transform() const
    {
        glm::mat4x4 result(1.0f);

        result = glm::translate(result, pos_);

        result = glm::scale(result, scale_);

        result = glm::rotate(result, glm::radians(euler_.x), {1.0f, 0, 0});
        result = glm::rotate(result, glm::radians(euler_.y), {0, 1.0f, 0});
        result = glm::rotate(result, glm::radians(euler_.z), {0, 0, 1.0f});

        return result;
    }
}