#pragma once

#include "math.hpp"

class camera
{
public:
    camera();

private:
    // vec3 m_position, m_rotation;
    // float m_radius;

    // mat4x4 m_view, m_iview;
    mat4x4 m_view, m_proj;
};