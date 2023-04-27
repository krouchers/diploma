#include <stdexcept>
#include <iostream>
#include <cmath>
#include <utility>

#include "opengl.hpp"
#include "sdl_window/window.hpp"
#include "utils/log.hpp"
#include "glad.hpp"
#include "shader.hpp"

void APIENTRY
DebugProc(GLenum source,
          GLenum type,
          [[maybe_unused]] GLuint id,
          GLenum severity,
          [[maybe_unused]] GLsizei length,
          [[maybe_unused]] const GLchar *message,
          [[maybe_unused]] const void *user_param)
{
    std::string src{};
    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        src = "API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        src = "Window system";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        src = "shader compiler";
        break;
    default:
        src = "unknown";
        break;
    }

    std::string tp{};
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        tp = "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        tp = "Depricated behavior";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        tp = "Undefined behavior";
        break;
    default:
        tp = "Unknown type of message";
        break;
    }

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
    case GL_DEBUG_SEVERITY_MEDIUM:
    default:
        break;
    }
    warn("Source: %s, Type: %s: %s", src.c_str(), tp.c_str(), message);
}

Opengl::Opengl(std::shared_ptr<IWindow> &win)
    : window_{win}
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    info("Creating GL context");
    gl_context_ = SDL_GL_CreateContext(reinterpret_cast<SDL_Window *>(win->GetHandler()));
    if (gl_context_ == nullptr)
    {
        throw std::runtime_error("Failed to create GL context");
    }

    if (SDL_GL_MakeCurrent(reinterpret_cast<SDL_Window *>(win->GetHandler()), gl_context_))
    {
        throw std::runtime_error("Failed to make gl context current for created window");
    }

    info("Loading glad");
    if (!gladLoadGL())
    {
        throw std::runtime_error("faile to load glad");
    }

    info("GL Version is %s", Version().c_str());

    SetupDebugProc();
    SDL_GL_SetSwapInterval(1);
}

Opengl::~Opengl()
{
    info("Destroing GL context");
    SDL_GL_DeleteContext(gl_context_);
}

void Opengl::SetupDebugProc()
{
    info("Settin up debug proc for gl");
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugProc, nullptr);
}

std::string Opengl::Version()
{
    return {(char *)glGetString(GL_VERSION)};
};

void *Opengl::GetHandler()
{
    return gl_context_;
}

void Opengl::SwapFrame()
{
    window_->SwapFrame();
}

void Opengl::InitGlobalParams()
{
    glEnable(GL_DEPTH_TEST);
}