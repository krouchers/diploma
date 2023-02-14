#pragma once
#include <string>

#include "glm/vec2.hpp"
#include "SDL.h"

class window
{
public:
    window(std::string window_name, glm::vec2 size = {1280, 720});
    ~window();

    SDL_Window *get_sdl_handler() const;
    void poll_event();

private:
    glm::vec2 size_{1280, 720};
    std::string name_;
    SDL_Window *sdl_handler_;
    void create_window();
};