#pragma once

#include "math.hpp"

class Camera
{
public:
    Camera(Vec2 dim);

    Mat4x4 GetProjection();
    Mat4x4 GetView();

private:
    void Reset();
    void SetAs(float as);

    // vec3 m_position, m_rotation;
    float fov_, near_plane_, far_plane_, aspect_ratio_;

    // Vec2 dim_;

    // Mat4x4 m_view, m_iview;
    Mat4x4 view_, proj_;
};