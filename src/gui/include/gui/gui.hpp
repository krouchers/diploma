#pragma once
#include <iostream>
#include <memory>

#include "definitions.hpp"
#include "interfaces/gui.hpp"
#include "interfaces/window.hpp"
#include "lines.hpp"
#include "camera.hpp"
#include "scene/scene.hpp"

class Opengl;

namespace Color
{
    inline glm::vec3 red{glm::vec3{163.f, 66, 81} / 255.f};
    inline glm::vec3 blue{glm::vec3{64.f, 127.f, 193.f} / 255.f};
    inline glm::vec3 baseplane{glm::vec3{71, 71, 71} / 255.f};
    inline glm::vec3 white{glm::vec3{1, 1, 1}};
}
class DearGui : public IGui
{

public:
    DearGui(std::shared_ptr<Opengl> &gl,
            std::shared_ptr<IWindow> &window,
            std::shared_ptr<Camera> &cam);
    void AddSlider(const std::string &name, float &value);
    void ProcessEvent(const Event &) final;
    void CreateBaseLine();
    void Render3D(Scene &) final;
    void RenderUi() final;

private:
    std::shared_ptr<IWindow> window_;
    std::shared_ptr<Opengl> gl_;
    std::shared_ptr<Camera> camera_;

    gl::Lines baseline_{};
};