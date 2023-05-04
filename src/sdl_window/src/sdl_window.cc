#include "sdl_window/window.hpp"

SdlWindow::SdlWindow(std::string const &name, glm::vec2 const &size)
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
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
}

float SdlWindow::GetAspectRatio()
{
    return size_[1] / size_[0];
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

glm::vec2 SdlWindow::GetSize()
{
    return size_;
}