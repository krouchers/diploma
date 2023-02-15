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
        throw std::runtime_error("Failed to create window");
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
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

std::vector<event> window::poll_events()
{
    SDL_Event e;
    std::vector<event> events;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            events.push_back(event::QUIT);
    }
    return events;
}