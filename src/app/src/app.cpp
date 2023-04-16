#include "app.hpp"
#include "log.hpp"
#include "window/sdl_window.hpp"
#include "opengl.hpp"

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
    while (!m_window->should_quit())
    {
        m_gl->render();
    }
}
