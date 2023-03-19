#include <stdexcept>
#include <iostream>
#include <cmath>
#include <utility>

#include "graphic.hpp"
#include "window.hpp"
#include "log.hpp"
#include "glad.hpp"
#include "mesh.hpp"

void APIENTRY
debug_proc(GLenum source,
           GLenum type,
           [[maybe_unused]] GLuint id,
           GLenum severity,
           [[maybe_unused]] GLsizei length,
           [[maybe_unused]] const GLchar *message,
           [[maybe_unused]] const void *userParam)
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

graphic::graphic(const std::shared_ptr<window> win)
    : window_{win}
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    info("Creating GL context");
    gl_context_ = SDL_GL_CreateContext(window_->get_sdl_handler());
    if (!gl_context_)
    {
        throw std::runtime_error("Failed to create GL context");
    }

    if (SDL_GL_MakeCurrent(window_->get_sdl_handler(), gl_context_))
    {
        throw std::runtime_error("Failed to make gl context current for created window");
    }

    info("Loading glad");
    if (!gladLoadGL())
    {
        throw std::runtime_error("faile to load glad");
    }

    info("GL Version is %s", version().c_str());

    setup_debug_proc();
    SDL_GL_SetSwapInterval(1);

    info("Compiling and loading shaders...");
    shader_.load(shaders::vertex_shader, shaders::fragment_shader);
    rect = mesh(std::move(vertex_data), std::move(indices));
    // FIXME: there gonna be ralative path
    m_tex1 = tex2D("C:/Users/filin/coding/diploma/assets/container.jpg");
    m_tex2 = tex2D("C:/Users/filin/coding/diploma/assets/awesomeface.png");
    shader_.set("tex1", 0);
    shader_.set("tex2", 1);
}

void graphic::render()
{
    glClearColor(1.0f, 0.0f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader_.bind();
    m_tex1.bind(0);
    m_tex2.bind(1);
    rect.render();
    SDL_GL_SwapWindow(window_->get_sdl_handler());
}

graphic::~graphic()
{
    info("Destroing GL context");
    SDL_GL_DeleteContext(gl_context_);
}

void graphic::setup_debug_proc()
{
    info("Settin up debug proc for gl");
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debug_proc, nullptr);
}

std::string graphic::version()
{
    return {(char *)glGetString(GL_VERSION)};
};