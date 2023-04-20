#pragma once
#include <iostream>
#include <exception>

#include "definitions.hpp"
#include <window_interface.hpp>
#include "SDL.h"
#include "log.hpp"

class GEODIP_API SdlWindow : public IWindow
{
public:
    void CreateWindow(std::string const &window_name, Vec2 const &size) final;
    float GetAspectRatio() final;
    bool ShouldQuit() final;
    void *GetHandler() final;
    void Close() final;

    SDL_Window *m_sdl_handler{nullptr};

private:
    Vec2 size_{1280, 720};
    std::string name_{};
};