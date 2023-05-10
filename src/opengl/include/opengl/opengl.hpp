#pragma once

#include <memory>
#include <string>
#include <utility>

#include "opengl/tex2D.hpp"
#include "utils/camera.hpp"
#include "sdl_window/window.hpp"
#include "opengl/shader.hpp"

class Opengl
{
public:
    Opengl(std::shared_ptr<IWindow> &);
    ~Opengl();

    Opengl(const Opengl &) = delete;
    Opengl &operator=(const Opengl &) = delete;

    Opengl(Opengl &&) = delete;
    Opengl &operator=(Opengl &&) = delete;

    void *GetHandler();
    void SwapFrame();
    void InitGlobalParams();

private:
    void SetupDebugProc();

    std::shared_ptr<IWindow> window_;
    SDL_GLContext gl_context_;
    std::string Version();
};

namespace gl
{
    void ColorOutput(bool enable);
}
