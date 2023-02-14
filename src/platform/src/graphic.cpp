#include <stdexcept>
#include <iostream>

#include "graphic.hpp"
#include "window.hpp"
#include "log.hpp"
#include "glad.hpp"

void APIENTRY
debug_proc(GLenum source,
           GLenum type,
           GLuint id,
           GLenum severity,
           GLsizei length,
           const GLchar *message,
           const void *userParam)
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
        warn("Source: %s, Type: %s", src.c_str(), tp.c_str());
    default:
        break;
    }
}

graphic::graphic(const window &win)
{
    info("Creating GL context");
    gl_context_ = SDL_GL_CreateContext(win.get_sdl_handler());
    if (!gl_context_)
    {
        throw std::runtime_error("Faile to create GL context");
    }

    info("Loading glad");
    if (!gladLoadGL())
    {
        throw std::runtime_error("faile to load glad");
    }

    info("GL Version is %s", version().c_str());

    setup_debug_proc();

    info("Creating VAO...");
    glGenVertexArrays(1, &VAO);
    const GLfloat vertex_data[]{-1.0, 1.0, 0.0,
                                1.0, -1.0, 0.0,
                                0.0, 1.0, 0.0};

    glBindBuffer(GL_ARRAY_BUFFER, VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    shader_.load(shaders::vertex_shader, shaders::fragment_shader);
}

void graphic::render()
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
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