#pragma once
#include <memory>

#include "camera.hpp"
#include "window_interface.hpp"
// #include "gui/gui.hpp"

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
    std::unique_ptr<opengl> m_gl;

    camera m_camera;
    // gui m_gui;
};
