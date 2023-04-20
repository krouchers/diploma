#pragma once
#include <memory>

#include "camera.hpp"
#include "window_interface.hpp"
#include "scene/scene.hpp"
// #include "gui/gui.hpp"

class App
{
public:
    App();
    void Run();

    ~App();

private:
    App(const App &) = delete;
    App &operator=(const App &) = delete;

    App(App &&) = delete;
    App &operator=(App &&) = delete;

    std::shared_ptr<IWindow> window_;
    // std::unique_ptr<Opengl> gl_;

    Camera camera_;

    Scene scene_;
    // gui m_gui;
};
