#pragma once
#include <iostream>
#include <memory>
#include <filesystem>

#include "definitions.hpp"
#include "interfaces/gui.hpp"
#include "interfaces/window.hpp"
#include "lines.hpp"
#include "utils/camera.hpp"
#include "scene/scene.hpp"

class Opengl;

namespace Color
{
    inline glm::vec3 red{glm::vec3{163.f, 66, 81} / 255.f};
    inline glm::vec3 blue{glm::vec3{64.f, 127.f, 193.f} / 255.f};
    inline glm::vec3 baseplane{glm::vec3{71, 71, 71} / 255.f};
    inline glm::vec3 white{glm::vec3{1, 1, 1}};
}
class GEODIP_API DearGui : public IGui
{

public:
    DearGui(std::shared_ptr<Opengl> &gl,
            std::shared_ptr<IWindow> &window,
            std::shared_ptr<Camera> &cam,
            std::shared_ptr<Scene> &scene,
            std::string const &exe_path);
    void AddSlider(const std::string &name, float &value);
    void ProcessEvent(const Event &) final;
    void CreateBaseLine();
    void Render3D(Scene &) final;
    void RenderUi() final;
    void UIMenu();
    void UINewObj();
    void UISideMenu();
    virtual ~DearGui() = default;

private:
    std::shared_ptr<IWindow> window_;
    std::shared_ptr<Opengl> gl_;
    std::shared_ptr<Camera> camera_;
    std::shared_ptr<Scene> scene_;

    bool newObjWindow{false};

    gl::Lines baseline_{};
};