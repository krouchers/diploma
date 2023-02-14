#include <iostream>
#include <exception>

#include "window.hpp"
#include "SDL.h"
#include "log.hpp"

void window::create_window()
{
    info("Initializing SDL");
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        throw std::runtime_error("Failed to init sdl");
    }
    info("Creating window");

    sdl_handler_ = SDL_CreateWindow("some window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    size_.x, size_.y, SDL_WINDOW_OPENGL);
    if (!sdl_handler_)
    {
        throw std::runtime_error("Faile to create window");
    }
}

SDL_Window *window::get_sdl_handler() const
{
    return sdl_handler_;
}

window::window(std::string window_name, glm::vec2 size)
    : size_{size}, name_{window_name}
{
    create_window();
}

window::~window()
{
    info("Destroing window");
    SDL_DestroyWindow(sdl_handler_);
}

void window::poll_event()
{
    SDL_Event e;
    SDL_PollEvent(&e);
}