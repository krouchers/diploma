#include "window/sdl_window.hpp"

void SdlWindow::CreateWindow(std::string const &window_name, Vec2 const &size)
{
    size_ = size;
    info("Initializing SDL");
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        throw std::runtime_error("Failed to init sdl");
    }

    info("Creating window");
    m_sdl_handler = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                     size.x, size.y, SDL_WINDOW_OPENGL);
    if (!m_sdl_handler)
    {
        throw std::runtime_error("Failed to create window");
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
}

float SdlWindow::GetAspectRatio()
{
    return size_.y / size_.x;
}

bool SdlWindow::ShouldQuit()
{
    return should_quit_;
}

void *SdlWindow::GetHandler()
{
    return m_sdl_handler;
}

void sdl_window::close()
{
    should_quit_ = true;
}