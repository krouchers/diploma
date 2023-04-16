#pragma once
#include <iostream>
#include <exception>

#include "definitions.hpp"
#include <window_interface.hpp>
#include "SDL.h"
#include "log.hpp"

class sdl_window : public IWindow
{
public:
    void create_window(std::string const &window_name, vec2 const &size) final;
    float get_aspect_ratio() final;
    bool should_quit() final;
    void *get_handler() final;

    SDL_Window *m_sdl_handler{nullptr};

private:
    vec2 m_size{1280, 720};
    std::string m_name{};
};