#include "gui/gui.hpp"
#include "log.hpp"
#include "opengl.hpp"
#include "SDL.h"
#include "scene/renderer.hpp"
#include "scene/scene.hpp"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

DearGui::DearGui(std::shared_ptr<Opengl> &gl,
                 std::shared_ptr<IWindow> &window,
                 std::shared_ptr<Camera> &cam)
    : window_{window}, gl_{gl}, camera_{cam}
{
    info("Initializing DearGui...");

    ImGui::CreateContext();
    auto &io{ImGui::GetIO()};
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplSDL2_InitForOpenGL(
        reinterpret_cast<SDL_Window *>(window_->GetHandler()),
        reinterpret_cast<SDL_GLContext *>(gl_->GetHandler()));
    ImGui_ImplOpenGL3_Init(nullptr);

    CreateBaseLine();
}

void DearGui::AddSlider(const std::string &name, float &value)
{
    ImGui::SliderFloat(name.c_str(), &value, 0.0f, 1.0f, "ratio = %.3f");
}

void DearGui::ProcessEvent(const Event &e)
{
    ImGui_ImplSDL2_ProcessEvent(reinterpret_cast<const SDL_Event *>(e.GetEventRawHandle()));
}

void DearGui::RenderUi()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);
    static float angle{0};
    AddSlider("angle", angle);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    scene::Renderer::Get().Lines(baseline_, camera_->GetView());
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
                   { item.Render(camera_->GetProjection() * camera_->GetView()); });

    scene::Renderer::Get().Lines(baseline_, camera_->GetProjection() * camera_->GetView());
}