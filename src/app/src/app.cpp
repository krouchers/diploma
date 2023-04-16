#include "app.hpp"
#include "log.hpp"
#include "window/sdl_window.hpp"
#include "opengl.hpp"
#include "math.hpp"

app::app()
    : m_window{new sdl_window{}},
      m_camera{{1280, 720}}
{
    m_window->create_window("Geodip", {1280, 720});
    m_gl = std::make_unique<opengl>(m_window, m_camera);
}

app::~app() = default;

void app::run()
{

    mat4x4 mat = mat4x4::get_projection_matrix(2.f, 10, 45, 720. / 1280.) * mat4x4::get_rotation_matrix(vec3{0, 0, 12});
    std::vector<vec4> vertex_data{
        {-0.5f, -0.5f, -10.0f, 1.},
        {0.5f, -0.5f, -10.0f, 1.},
        {0.5f, 0.5f, -10.0f, 1.},
        {-0.5f, 0.5f, -10.0f, 1.}};

    for (int i = 0; i < 4; ++i)
    {
        vec4 res = mat * vertex_data[i];
        res = res / res.w_;
        std::cout << res.x_ << " " << res.y_ << " " << res.z_ << " " << res.w_ << '\n';
    }

    while (!m_window->should_quit())
    {
        m_gl->render();
    }
}
