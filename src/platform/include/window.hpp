#pragma once
#include <string>
#include <vector>

#include "glm/vec2.hpp"
#include "SDL.h"

enum class event
{
    QUIT
};

class window
{
public:
    window(std::string window_name, glm::vec2 size = {1280, 720});
    ~window();

    inline SDL_Window *get_sdl_handler() const noexcept { return sdl_handler_; }
    std::vector<event> poll_events();

private:
    glm::vec2 size_{1280, 720};
    std::string name_;
    SDL_Window *sdl_handler_;
    void create_window();
};