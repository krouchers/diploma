#pragma once
#include <memory>

#include "camera.hpp"
#include "window_interface.hpp"
#include "gui_interface.hpp"
#include "gui.hpp"

class opengl;

class app
{
public:
    app();
    app(app &&);
    void run();

    ~app();

private:
    app(const app &) = delete;
    app &operator=(const app &) = delete;

    std::shared_ptr<IWindow> m_window;
    std::shared_ptr<opengl> m_gl;
    std::shared_ptr<IGui> m_gui;

    camera m_camera;
};
