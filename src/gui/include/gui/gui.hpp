#pragma once
#include <iostream>
#include <memory>
#include <filesystem>

#include "definitions.hpp"
#include "colors.hpp"
#include "interfaces/gui.hpp"
#include "interfaces/window.hpp"
#include "opengl/lines.hpp"
#include "utils/camera.hpp"
#include "scene/scene.hpp"
#include "gui/editor.hpp"

class Opengl;

namespace gui
{
    class GEODIP_API DearGui : public IGui
    {

    public:
        DearGui(std::shared_ptr<Opengl> &gl,
                std::shared_ptr<IWindow> &window,
                std::shared_ptr<Camera> &cam,
                std::shared_ptr<Scene> &scene,
                std::string const &exe_path);
        void ProcessEvent(const Event &) final;
        void CreateBaseLine();
        void Render3D(Scene &) final;
        void RenderUi() final;
        void Drag() final;
        glm::vec2 UIMenu();
        void UINewObj();
        void UISideMenu(glm::vec2 const &pos);
        void ItemOptions();
        virtual ~DearGui() = default;
        glm::vec3 ClickDirection(glm::vec2 screen_pos);

    private:
        std::shared_ptr<IWindow> window_;
        std::shared_ptr<Opengl> gl_;
        std::shared_ptr<Camera> camera_;
        std::shared_ptr<Scene> scene_;

        bool newObjWindow{false};

        gl::Lines baseline_{};

        Editor editor_;
        Widgets widgets_;

        bool unselection_{false};

        // debug section
        glm::vec2 ndc_pos_;
        glm::vec4 world_pos_;
        //
    };

}