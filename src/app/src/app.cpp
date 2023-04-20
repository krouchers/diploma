#include "app.hpp"
#include "log.hpp"
#include "window/sdl_window.hpp"
#include "opengl.hpp"
#include "math.hpp"
#include "gui.hpp"
#include "opengl.hpp"
#include "scene/renderer.hpp"
#include "scene/item.hpp"

App::App()
    : window_{new SdlWindow{}},
      camera_{{1280, 720}}
{
    window_->create_window("Geodip", {1280, 720});
    gui_ = std::shared_ptr<IGui>(new dear_gui{m_gl, m_window});

    gui_->init();
    window_->CreateWindow("Geodip", {1280, 720});
    // gl_ = std::make_unique<Opengl>(window_, camera_);
    scene::Renderer::Setup(window_, camera_);

    std::vector<Vert> vertex_data{
        {{-0.5f, -0.5f, -2.f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -2.f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -2.f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -2.f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}};
    std::vector<GLuint> indices{0, 1, 2, 0, 2, 3};

    scene_.Add(scene::Item(gl::Mesh(std::move(vertex_data), std::move(indices))));
}

App::~App() = default;

void App::Run()
{
    while (!window_->ShouldQuit())
    {
        auto &r = scene::Renderer::Get();
        r.SetProjectionMatrix(camera_.GetProjection());

        r.begin();
        r.Render3D(scene_, camera_);
        gui_->render();
        r.end();
    }
}
