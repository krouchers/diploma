#include "camera.hpp"

camera::camera()
    : m_view{mat4x4::get_rotation_matrix(vec3{0, 0, 45})},
      m_proj{mat4x4::get_project_matrix()}
{
}