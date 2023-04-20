#include "app.hpp"
#include "log.hpp"
#include "window/sdl_window.hpp"
#include "opengl.hpp"
#include "math.hpp"
#include "gui/gui.hpp"
#include "opengl.hpp"
#include "scene/renderer.hpp"
#include "scene/item.hpp"

App::App()
    : window_{new SdlWindow{"Geodip", {1280, 720}}},
      gl_{new Opengl{window_}},
      gui_{new DearGui{gl_, window_}},
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
        auto &r = scene::Renderer::Get();
        r.Clear();
        r.Render3D(scene_, camera_);
        gui_->Render();
        window_->SwapFrame();
    }
}
