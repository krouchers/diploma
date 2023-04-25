#pragma once
#include <memory>

#include "camera.hpp"
#include "interfaces/window.hpp"
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

    void ProcessEvents();

    std::shared_ptr<IWindow> window_;
    std::shared_ptr<Opengl> gl_;
    std::shared_ptr<Camera> camera_;
    std::shared_ptr<IGui> gui_;

    enum class CameraMode
    {
        none,
        orbit,
        move
    };

    CameraMode camera_mode{CameraMode::none};

    Scene scene_;
};
