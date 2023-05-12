#include "scene/pose.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace scene
{
    glm::mat4x4 Pose::Transform() const
    {
        return glm::translate(glm::mat4x4(1.0f), pos_) *
               glm::rotate(glm::mat4x4(1.0f), glm::radians(euler_.z), {0.0f, 0.0f, 1.0f}) *
               glm::rotate(glm::mat4x4(1.0f), glm::radians(euler_.y), {0.0f, 1.0f, 0.0f}) *
               glm::rotate(glm::mat4x4(1.0f), glm::radians(euler_.x), {1.0f, 0.0f, 0.0f}) *
               glm::scale(glm::mat4x4(1.0f), scale_);
    }
}