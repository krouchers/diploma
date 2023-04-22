#include "app.hpp"
#include "log.hpp"
#include "sdl_window/window.hpp"
#include "sdl_window/event.hpp"
#include "opengl.hpp"
#include "math.hpp"
#include "gui/gui.hpp"
#include "opengl.hpp"
#include "scene/renderer.hpp"
#include "scene/item.hpp"

App::App()
    : window_{std::make_shared<SdlWindow>("Geodip", Vec2{1280, 720})},
      gl_{std::make_shared<Opengl>(window_)},
      gui_{std::make_shared<DearGui>(gl_, window_)},
      camera_{{1280, 720}}

{
    scene::Renderer::Setup(gl_);
    std::vector<Vert> vertex_data{
        {{-0.5f, -0.5f, -3.f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -3.f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -3.f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -3.f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}};
    std::vector<GLuint> indices{0, 1, 2, 0, 2, 3};

    scene_.Add(scene::Item(gl::Mesh(std::move(vertex_data), std::move(indices))));
}

App::~App() = default;

void App::Run()
{
    while (!window_->ShouldQuit())
    {
        SDLEvent e;
        SDL_Event sdl_e;
        while (SDL_PollEvent(&sdl_e))
        {
            e.e_ = sdl_e;
            gui_->ProcessEvent(e);
            switch (sdl_e.type)
            {
            case SDL_QUIT:
                window_->Close();
                break;
            }
        }
        auto &r = scene::Renderer::Get();
        r.Clear();
        r.Render3D(scene_, camera_);
        gui_->Render();
        window_->SwapFrame();
    }
}
