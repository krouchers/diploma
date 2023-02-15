#include <stdexcept>
#include <iostream>

#include "graphic.hpp"
#include "window.hpp"
#include "log.hpp"
#include "glad.hpp"

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

    SDL_GL_SetSwapInterval(1);
    info("Loading glad");
    if (!gladLoadGL())
    {
        throw std::runtime_error("faile to load glad");
    }

    info("GL Version is %s", version().c_str());

    setup_debug_proc();

    info("Creating VAO...");
    glGenVertexArrays(1, &VAO_);

    glBindVertexArray(VAO_);
    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    const GLfloat vertex_data[]{-1.0f, -1.0f, 0.0f,
                                1.0f, -1.0f, 0.0f,
                                0.0f, 1.0f, 0.0f};
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

    info("Compiling and loading shaders...");
    shader_.load(shaders::vertex_shader, shaders::fragment_shader);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void graphic::render()
{
    glUseProgram(shader_.get_program_id());
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
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