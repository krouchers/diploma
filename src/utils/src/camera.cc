#include "camera.hpp"

camera::camera(vec2 dim)
    : m_view{mat4x4::get_rotation_matrix(vec3{0, 0, 45})},
      m_proj{mat4x4::get_projection_matrix(2, 10, 45, dim.y / dim.x)}
{
}