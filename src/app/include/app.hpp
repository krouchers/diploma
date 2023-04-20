#pragma once
#include <memory>

#include "camera.hpp"
#include "window_interface.hpp"
#include "gui/gui.hpp"
#include "scene/scene.hpp"

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
    std::shared_ptr<Opengl> gl_;
    std::shared_ptr<IGui> gui_;

    Camera camera_;

    Scene scene_;
};
