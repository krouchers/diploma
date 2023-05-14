#include "gui/gui.hpp"
#include "utils/log.hpp"
#include "opengl/opengl.hpp"
#include "SDL.h"

#include "utils/generate_primitives.hpp"

#include "geometry/halfedge_mesh.hpp"

#include "scene/renderer.hpp"
#include "scene/scene.hpp"
#include "scene/item.hpp"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

namespace gui
{

    DearGui::DearGui(std::shared_ptr<Opengl> &gl,
                     std::shared_ptr<IWindow> &window,
                     std::shared_ptr<Camera> &cam,
                     std::shared_ptr<Scene> &scene,
                     std::string const &exe_path)
        : window_{window}, gl_{gl}, camera_{cam}, scene_{scene}
    {
        info("Initializing DearGui...");

        ImGui::CreateContext();
        auto &io{ImGui::GetIO()};
        io.Fonts->AddFontFromFileTTF(
            std::filesystem::path{exe_path}.parent_path().parent_path().append("fonts").append("Anonymous_Pro.ttf").string().c_str(), 16.0f,
            nullptr, io.Fonts->GetGlyphRangesCyrillic());

        ImGui_ImplSDL2_InitForOpenGL(
            reinterpret_cast<SDL_Window *>(window_->GetHandler()),
            reinterpret_cast<SDL_GLContext *>(gl_->GetHandler()));
        ImGui_ImplOpenGL3_Init(nullptr);

        CreateBaseLine();
    }

    void DearGui::ProcessEvent(const Event &e)
    {
        const SDL_Event *event = reinterpret_cast<const SDL_Event *>(e.GetEventRawHandle());
        ImGui_ImplSDL2_ProcessEvent(event);
        if (ImGui::GetIO().WantCaptureMouse)
            return;
        switch (event->type)
        {
        case SDL_MOUSEBUTTONDOWN:
        {
            if (event->button.button == SDL_BUTTON_LEFT)
            {
                auto &r = scene::Renderer::Get();
                SceneID id = r.ReadID({event->button.x, event->button.y});
                layout_.Select(id);
                widgets_.Select(id);
                if (widgets_.dragging_)
                {
                    scene::Item &obj = scene_->Get(layout_.selected_object_).value();
                    widgets_.StartDrag(
                        obj.pose_.pos_,
                        ClickDirection({event->button.x, event->button.y}),
                        camera_->GetPosition());
                }
                if (id == 0)
                    unselection_ = true;
            }
            break;
        }
        case SDL_MOUSEMOTION:
        {
            if (widgets_.dragging_)
            {
                auto obj_opt = scene_->Get(layout_.selected_object_);
                widgets_.DragTo(obj_opt.value().get().pose_.pos_,
                                ClickDirection({event->button.x, event->button.y}),
                                camera_->GetPosition());
                obj_opt.value().get().pose_ = widgets_.ApplyAction(obj_opt.value().get().pose_);
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            if (unselection_)
            {
                layout_.ClearSelection();
                unselection_ = false;
            }
            if (widgets_.dragging_)
            {
                widgets_.EndDrag();
            }
            break;
        }
        }
    }

    void DearGui::RenderUi()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        auto next_pos = UIMenu();
        UISideMenu(next_pos);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void DearGui::CreateBaseLine()
    {
        int z, x;
        z = x = 20;
        float length{40};
        for (int i = -z; i <= z; ++i)
        {
            if (i == 0)
            {
                baseline_.Add({-length / 2, 0, i}, {length / 2, 0, i}, {Color::red});
                continue;
            }
            baseline_.Add({-length / 2, 0, i}, {length / 2, 0, i}, {Color::baseplane});
        }

        for (int i = -x; i <= x; ++i)
        {
            if (i == 0)
            {
                baseline_.Add({i, 0, -length / 2}, {i, 0, length / 2}, {Color::blue});
                continue;
            }
            baseline_.Add({i, 0, -length / 2}, {i, 0, length / 2}, {Color::baseplane});
        }
    }

    void DearGui::Render3D(Scene &scene)
    {
        if (mode_ == Mode::layout)
        {
            scene.ForItems([&](scene::Item &item)
                           { item.Render(); });
        }

        scene::Renderer::Get().Lines(baseline_, camera_->GetProjection() * camera_->GetView());

        switch (mode_)
        {
        case Mode::layout:
            layout_.Render(scene_->Get(layout_.GetSelectedSceneID()), widgets_);
            break;
        case Mode::model:
            model_.Render(scene_->Get(layout_.GetSelectedSceneID()), widgets_);
            break;
        }
    }

    glm::vec2 DearGui::UIMenu()
    {
        float next_window_pos{};
        ImGui::BeginMainMenuBar();
        if (ImGui::Button("Добавить фигуру"))
        {
            newObjWindow = true;
        }
        if (ImGui::Button("Редактировать положение"))
        {
            mode_ = Mode::layout;
        }
        if (ImGui::Button("Редактировать модель"))
        {
            mode_ = Mode::model;
        }
        next_window_pos = ImGui::GetWindowSize().y;
        ImGui::EndMainMenuBar();

        ImGui::Begin("debug");
        auto pos = camera_->GetPosition();
        ImGui::Text("Camera pos: (%f, %f, %f)", pos.x, pos.y, pos.z);
        ImGui::Text("Current selection: %d", layout_.GetSelectedSceneID());
        auto obj_opt = scene_->Get(layout_.selected_object_);
        if (obj_opt)
        {
            auto sel_pos = obj_opt.value().get().pose_.pos_;
            auto sel_rot = obj_opt.value().get().pose_.euler_;
            ImGui::Text("Selection pos: (%f, %f, %f)", sel_pos.x, sel_pos.y, sel_pos.z);
            ImGui::Text("Selection rot: (%f, %f, %f)", sel_rot.x, sel_rot.y, sel_rot.z);
            ImGui::Text("Rotation degrees: %f", widgets_.rotation_degrees_);
        }
        ImGui::Text("Axis selection: %d", widgets_.axis_);
        ImGui::Text("Started Dragging?: %d", widgets_.dragging_);

        ImGui::Text("ndc_pos: (%f, %f)", ndc_pos_.x, ndc_pos_.y);
        ImGui::Text("World pos: (%f, %f, %f, %f)", world_pos_.x, world_pos_.y, world_pos_.z, world_pos_.w);

        ImGui::Text("plane_sel_pos_f: (%f, %f, %f)", widgets_.plane_selection_pos_f_.x, widgets_.plane_selection_pos_f_.y, widgets_.plane_selection_pos_f_.z);
        ImGui::Text("plane_sel_pos_s: (%f, %f, %f)", widgets_.plane_selection_pos_s_.x, widgets_.plane_selection_pos_s_.y, widgets_.plane_selection_pos_s_.z);
        ImGui::Text("move_sel_pos: (%f, %f, %f)", widgets_.move_selection_pos_.x, widgets_.move_selection_pos_.y, widgets_.move_selection_pos_.z);
        ImGui::End();
        if (newObjWindow)
        {
            UINewObj();
        }

        return {0, next_window_pos};
    }

    void DearGui::UINewObj()
    {
        auto AddMesh{
            [this](geometry::Mesh &&mesh)
            {
                geometry::HalfedgeMesh hm{};
                hm.CreateFromMesh(std::move(mesh));
                scene_->Add(std::move(hm));
                newObjWindow = false;
            }};
        ImGui::Begin("Добавить фигуру", &newObjWindow);
        if (ImGui::CollapsingHeader("Куб"))
        {
            static float edgeLenght{};
            ImGui::SliderFloat("Длина ребра", &edgeLenght, 1.0f, 10.0f);
            if (ImGui::Button("Добавить"))
            {
                auto [verts, inds]{utils::GenerateCube(edgeLenght / 2)};
                AddMesh(geometry::Mesh{std::move(verts), std::move(inds)});
            }
        }
        if (ImGui::CollapsingHeader("Стрелку"))
        {
            if (ImGui::Button("Добавить"))
            {
                AddMesh(utils::GenerateArrow());
            }
        }
        if (ImGui::CollapsingHeader("Тор"))
        {
            if (ImGui::Button("Добавить"))
            {
                AddMesh(utils::GenerateTorus(0.975f, 1.0f));
            }
        }
        if (ImGui::CollapsingHeader("Виджет для вращения"))
        {
            if (ImGui::Button("Добавить"))
            {
                AddMesh(utils::GenereateScaleMesh());
            }
        }
        if (ImGui::CollapsingHeader("Сфера"))
        {
            static float radius{};
            ImGui::SliderFloat("Длина ребра", &radius, 1.0f, 10.0f);
            if (ImGui::Button("Добавить"))
            {
                AddMesh(utils::GenerateSphere(radius, 3));
            }
        }
        ImGui::End();
    }

    void DearGui::Drag()
    {
    }

    glm::vec3 DearGui::ClickDirection(glm::vec2 screen_pos)
    {
        glm::vec2 ndc_pos{2.0f * screen_pos.x / 1280.0f - 1.0f,
                          1.0f - 2.0f * screen_pos.y / 720.0f};
        glm::vec4 world_pos = glm::inverse(camera_->GetProjection() * camera_->GetView()) *
                              glm::vec4{ndc_pos, -1.0f, 1.0f};
        ndc_pos_ = {ndc_pos.x, ndc_pos.y};
        world_pos_ = {world_pos.x, world_pos.y, world_pos.z, world_pos.w};
        return glm::normalize(glm::vec3(world_pos) - camera_->GetPosition());
    }

    void DearGui::UISideMenu(glm::vec2 const &pos)
    {
        ImGui::SetNextWindowPos({0.0f, pos.y});
        ImGui::SetNextWindowSize({1280.0f * 0.2, 720.0f - pos.y});
        ImGui::Begin("SideMenu", nullptr,
                     ImGuiWindowFlags_NoTitleBar |
                         ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_NoScrollbar |
                         ImGuiWindowFlags_NoCollapse |
                         ImGuiWindowFlags_NoSavedSettings);
        ImGui::Text("SDF");
        ItemOptions();
        ImGui::End();
    }

    void DearGui::ItemOptions()
    {
        if (ImGui::Button("Перемещать"))
        {
            widgets_.active_ = WidgetType::move;
        }
        if (ImGui::Button("Вращать"))
        {
            widgets_.active_ = WidgetType::rotate;
        }
        if (ImGui::Button("Масштабировать"))
        {
            widgets_.active_ = WidgetType::scale;
        }
    }
}