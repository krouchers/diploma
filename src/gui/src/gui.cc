#include "gui.hpp"
#include "log.hpp"
#include "opengl.hpp"
#include "SDL.h"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

void dear_gui::hello()
{
    std::cout << "hello world\n";
}

dear_gui::dear_gui(const std::shared_ptr<opengl> &gl,
                   const std::shared_ptr<IWindow> &window)
    : gl_{gl}, window_{window}
{
    info("Initializing dear_gui...");
}

void dear_gui::init()
{
    ImGui::CreateContext();
    auto &io{ImGui::GetIO()};
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplSDL2_InitForOpenGL(
        reinterpret_cast<SDL_Window *>(window_->get_handler()),
        reinterpret_cast<SDL_GLContext *>(gl_->get_handler()));
    ImGui_ImplOpenGL3_Init(nullptr);
}

void dear_gui::render()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        ImGui_ImplSDL2_ProcessEvent(&e);
        if (e.type == SDL_QUIT)
            window_->close();
    }
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}