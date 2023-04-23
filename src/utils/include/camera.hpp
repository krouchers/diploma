#pragma once

#include "math.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
    Camera(Vec2 dim);

    glm::mat4x4 GetView();
    glm::mat4x4 GetProjection();

    void MoveThroughOrbit(Vec2 offset);
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

    glm::mat4x4 rotation_, view_, projection_;
    glm::mat4x4 translation_;
};