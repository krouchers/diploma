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
    Opengl(const std::shared_ptr<IWindow> &);
    ~Opengl();

    Opengl(const Opengl &) = delete;
    Opengl &operator=(const Opengl &) = delete;

    Opengl(Opengl &&) = delete;
    Opengl &operator=(Opengl &&) = delete;

    void *GetHandler();
    void SwapFrame();

private:
    void SetupDebugProc();

    std::shared_ptr<IWindow> window_;
    SDL_GLContext gl_context_;
    std::string Version();
};
