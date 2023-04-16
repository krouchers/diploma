#pragma once

#include <memory>
#include <string>
#include <utility>

#include "SDL.h"
#include "mesh.hpp"
#include "tex2D.hpp"
#include "camera.hpp"
#include "window/sdl_window.hpp"
#include "shader.hpp"

class opengl
{
public:
    opengl(std::shared_ptr<IWindow> const &, camera const &);
    ~opengl();
    opengl(const opengl &) = delete;
    opengl &operator=(const opengl &) = delete;

    void render();

    // FIXME: That not should be there
    std::vector<vert> vertex_data{
        {{-0.5f, -0.5f, -2.f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -2.f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -2.f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -2.f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}};
    std::vector<GLuint> indices{0, 1, 2, 0, 2, 3};
    mesh rect;
    tex2D m_tex1;
    tex2D m_tex2;

private:
    void setup_debug_proc();

    std::shared_ptr<IWindow> window_;
    camera m_camera;
    SDL_GLContext gl_context_;
    std::string version();
    shader shader_;
};
