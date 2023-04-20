#include "app.hpp"
#include "log.hpp"
#include "window/sdl_window.hpp"
#include "opengl.hpp"
#include "math.hpp"
#include "gui.hpp"

app::app()
    : m_window{new sdl_window{}},
      m_camera{{1280, 720}}
{
    m_window->create_window("Geodip", {1280, 720});
    m_gl = std::shared_ptr<opengl>(new opengl{m_window, m_camera});
    m_gui = std::shared_ptr<IGui>(new dear_gui{m_gl, m_window});

    m_gui->init();
}

app::~app() = default;

void app::run()
{
    while (!m_window->should_quit())
    {
        m_gl->begin();
        m_gl->render();
        m_gui->render();
        m_gl->end();
    }
}
