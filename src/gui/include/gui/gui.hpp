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

#include "gui/layout.hpp"
#include "gui/model.hpp"
#include "gui/view.hpp"

class Opengl;

enum class Mode
{
    layout,
    model,
    view
};

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
        void DragTo(const glm::vec3 click_dir, const glm::vec3 cam_pos);
        void EndDrag();
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

        bool text_input_window_{false};

        bool newObjWindow{false};

        gl::Lines baseline_{};

        Layout layout_;
        Model model_;
        Widgets widgets_;
        View view_;

        Mode mode_{Mode::layout};

        bool unselection_{false};

        // debug section
        glm::vec2 ndc_pos_;
        glm::vec4 world_pos_;
        //
    };

}