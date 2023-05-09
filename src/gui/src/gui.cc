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
        switch (event->type)
        {
        case SDL_MOUSEBUTTONDOWN:
        {
            if (event->button.button == SDL_BUTTON_LEFT)
            {
                auto &r = scene::Renderer::Get();
                SceneID id = r.ReadID({event->button.x, event->button.y});
                editor_.Select(id);
                widgets_.Select(id);
                if (id == 0)
                    unselection_ = true;
            }
            break;
        }
        case SDL_MOUSEMOTION:
        {
            if (widgets_.dragging_)
            {
                auto obj_opt = scene_->Get(editor_.selected_object_);
                widgets_.Drag(obj_opt, ClickDirection({event->button.x,
                                                       event->button.y}));
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            if (unselection_)
            {
                editor_.ClearSelection();
                unselection_ = false;
            }
            if (widgets_.dragging_)
            {
                widgets_.dragging_ = false;
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

        UIMenu();

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

        scene.ForItems([&](scene::Item &item)
                       { item.Render(); });

        scene::Renderer::Get().Lines(baseline_, camera_->GetProjection() * camera_->GetView());

        editor_.Render(scene_->Get(editor_.GetSelectedSceneID()), widgets_);
    }

    void DearGui::UIMenu()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::Button("Добавить фигуру"))
            {
                newObjWindow = true;
            }
            ImGui::EndMainMenuBar();
        }

        ImGui::Begin("debug");
        auto pos = camera_->GetPosition();
        ImGui::Text("Camera pos: (%f, %f, %f)", pos.x, pos.y, pos.z);
        ImGui::Text("Current selection: %d", editor_.GetSelectedSceneID());
        ImGui::Text("Axis selection: %d", widgets_.axis_);
        ImGui::Text("Started Dragging?: %d", widgets_.dragging_);

        ImGui::Text("ndc_pos: (%f, %f)", ndc_pos_.x, ndc_pos_.y);
        ImGui::Text("World pos: (%f, %f, %f, %f)", world_pos_.x, world_pos_.y, world_pos_.z, world_pos_.w);
        ImGui::End();
        if (newObjWindow)
        {
            UINewObj();
        }
    }

    void DearGui::UINewObj()
    {
        auto AddMesh{
            [this](gl::Mesh &&mesh)
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
                AddMesh(gl::Mesh{std::move(verts), std::move(inds)});
            }
        }
        if (ImGui::CollapsingHeader("Стрелку"))
        {
            if (ImGui::Button("Добавить"))
            {
                AddMesh(utils::GenerateArrow());
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
        // return glm::normalize(world_pos - camera_->GetPosition());
        return {};
    }
}