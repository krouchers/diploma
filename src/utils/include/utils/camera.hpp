#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "math/quat.hpp"

class Camera
{
public:
    Camera(glm::vec2 const &dim);

    glm::mat4x4 GetView();
    glm::mat4x4 GetProjection();
    glm::vec3 GetPosition();

    void MoveThroughOrbit(glm::vec2 const &offset);
    void MoveThroughRadius(float offset);

private:
    void Reset();
    void UpdatePos();
    void UpdateView();
    void SetAs(float as);
    glm::vec3 Front();

    glm::vec3 position_;
    float fov_, near_plane_, far_plane_, aspect_ratio_;
    float radius_;

    /**
     * @brief Отвечают за скорость перемещения камеры.
     *
     */
    float rotation_speed_, radius_speed_, translation_speed_;

    // Vec2 dim_;

    glm::mat4x4 view_, projection_;
    math::Quat rotation_;
    glm::mat4x4 translation_;
};