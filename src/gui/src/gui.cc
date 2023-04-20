#include "gui/gui.hpp"
#include "log.hpp"
#include "opengl.hpp"
#include "SDL.h"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

DearGui::DearGui(const std::shared_ptr<Opengl> &gl,
                 const std::shared_ptr<IWindow> &window)
    : window_{window}, gl_{gl}
{
    info("Initializing DearGui...");

    ImGui::CreateContext();
    auto &io{ImGui::GetIO()};
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplSDL2_InitForOpenGL(
        reinterpret_cast<SDL_Window *>(window_->GetHandler()),
        reinterpret_cast<SDL_GLContext *>(gl_->GetHandler()));
    ImGui_ImplOpenGL3_Init(nullptr);
}

void DearGui::AddSlider(const std::string &name, float &value)
{
    ImGui::SliderFloat(name.c_str(), &value, 0.0f, 1.0f, "ratio = %.3f");
}

void DearGui::Render()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        ImGui_ImplSDL2_ProcessEvent(&e);
        if (e.type == SDL_QUIT)
            window_->Close();
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);
    static float angle{0};
    AddSlider("angle", angle);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}