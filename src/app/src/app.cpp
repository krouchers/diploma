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
      camera_{{window_->GetSize()}}

{
    scene::Renderer::Setup(gl_);
    std::vector<Vert> vertex_data{
        {{-5.f, -5.f, -0.f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{5.f, -5.f, -0.f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{5.f, 5.f, -0.f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-5.f, 5.f, -0.f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}};
    std::vector<GLuint> indices{0, 1, 2, 0, 2, 3};

    scene_.Add(scene::Item(gl::Mesh(std::move(vertex_data), std::move(indices))));
}

App::~App() = default;

void App::Run()
{
    while (!window_->ShouldQuit())
    {
        glViewport(0, 0, window_->GetSize().x, window_->GetSize().y);
        ProcessEvents();
        auto &r = scene::Renderer::Get();
        r.Clear();
        r.Render3D(scene_, camera_);
        gui_->Render();
        window_->SwapFrame();
    }
}

void App::ProcessEvents()
{
    SDLEvent e; // Adapter for Igui
    SDL_Event sdl_e;

    while (SDL_PollEvent(&sdl_e))
    {
        e.e_ = sdl_e;
        gui_->ProcessEvent(e);
        switch (sdl_e.type)
        {
        case SDL_MOUSEBUTTONDOWN:
        {
            if (sdl_e.button.button == SDL_BUTTON_MIDDLE)
                camera_mode = CameraMode::orbit;
            break;
        }
        case SDL_MOUSEMOTION:
        {
            if (camera_mode == CameraMode::orbit)
            {
                camera_.MoveThroughOrbit(
                    Vec2{static_cast<float>(sdl_e.motion.xrel),
                         static_cast<float>(sdl_e.motion.yrel)});
                info("mouse moved from to %d with delta %d", sdl_e.motion.x, sdl_e.motion.xrel);
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            camera_mode = CameraMode::none;
            break;
        }
        case SDL_MOUSEWHEEL:
        {
            camera_.MoveThroughRadius(sdl_e.wheel.y);
            break;
        }
        case SDL_QUIT:
        {
            window_->Close();
            break;
        }
        }
    }
}