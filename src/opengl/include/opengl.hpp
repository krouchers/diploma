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

class Opengl
{
public:
    Opengl(std::shared_ptr<IWindow> const &, Camera const &);
    ~Opengl();

    Opengl(const Opengl &) = delete;
    Opengl &operator=(const Opengl &) = delete;

    Opengl(Opengl &&) = delete;
    Opengl &operator=(Opengl &&) = delete;

    void Render();

    void *GetHandler();

    // FIXME: That not should be there
    Tex2D m_tex1;
    Tex2D m_tex2;

private:
    void SetupDebugProc();

    std::shared_ptr<IWindow> window_;
    Camera m_camera_;
    SDL_GLContext gl_context_;
    std::string Version();
};
