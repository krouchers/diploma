#include "window/sdl_window.hpp"

SdlWindow::SdlWindow(std::string const &name, Vec2 const &size)
    : size_{size}
{
    info("Initializing SDL");
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        throw std::runtime_error("Failed to init sdl");
    }

    info("Creating window");
    sdl_handler_ = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    size.x, size.y, SDL_WINDOW_OPENGL);
    if (!sdl_handler_)
    {
        throw std::runtime_error("Failed to create window");
    }
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
    return sdl_handler_;
}

void SdlWindow::Close()
{
    should_quit_ = true;
}

void SdlWindow::SwapFrame()
{
    SDL_GL_SwapWindow(sdl_handler_);
}