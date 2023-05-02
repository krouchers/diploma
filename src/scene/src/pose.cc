#include "scene/pose.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace scene
{
    glm::mat4x4 Pose::transform()
    {
        glm::mat4x4 result(1.0f);

        glm::scale(result, scale_);

        glm::rotate(result, glm::radians(euler_.x), {1.0f, 0, 0});
        glm::rotate(result, glm::radians(euler_.y), {0, 1.0f, 0});
        glm::rotate(result, glm::radians(euler_.z), {0, 0, 1.0f});

        glm::translate(result, pos_);

        return result;
    }
}