#include "app.hpp"
#include "utils/log.hpp"
#include "glm/vec3.hpp"

#include "sdl_window/window.hpp"
#include "sdl_window/event.hpp"

#include "opengl/opengl.hpp"
#include "gui/gui.hpp"

#include "scene/renderer.hpp"
#include "scene/item.hpp"

App::App(std::string exe_path)
    : window_{std::make_shared<SdlWindow>("Geodip", glm::vec2{1280, 720})},
      gl_{std::make_shared<Opengl>(window_)},
      camera_{std::make_shared<Camera>(window_->GetSize())},
      scene_{std::make_shared<Scene>()},
      gui_{std::make_shared<gui::DearGui>(gl_, window_, camera_, scene_, exe_path)}
{
    gl_->InitGlobalParams();
    scene::Renderer::Setup(gl_, camera_);
}

App::~App() = default;

void App::Run()
{
    while (!window_->ShouldQuit())
    {
        info("===============Start frame================");
        ProcessEvents();
        auto &r = scene::Renderer::Get();
        r.Clear();
        r.Begin();
        gui_->Render3D(*scene_);
        r.Complete();
        gui_->RenderUi();
        window_->SwapFrame();
        info("===============End frame  ================");
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
                camera_->MoveThroughOrbit(
                    glm::vec2{static_cast<float>(sdl_e.motion.xrel),
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
            camera_->MoveThroughRadius(sdl_e.wheel.y);
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