#include <iostream>
#include <exception>

#include "window.hpp"
#include "SDL.h"

void window::create_window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        throw std::runtime_error("Failed to init sdl");
    }
    auto window = SDL_CreateWindow("some window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    if(!window){
        throw std::runtime_error("Faile to create window");
    }
}

window::window(std::string window_name)
    : name_{window_name}
{
    create_window();
}