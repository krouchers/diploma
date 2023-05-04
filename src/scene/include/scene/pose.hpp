#pragma once
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace scene
{
    class Pose
    {
    public:
        glm::mat4x4 transform() const;

    private:
        glm::vec3 euler_{};
        glm::vec3 pos_{};
        glm::vec3 scale_{};
    };
}