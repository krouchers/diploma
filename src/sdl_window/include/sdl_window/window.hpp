#pragma once
#include <iostream>
#include <exception>
#include <optional>

#include "definitions.hpp"
#include "interfaces/window.hpp"
#include "SDL.h"
#include "log.hpp"

class GEODIP_API SdlWindow : public IWindow
{
public:
    SdlWindow(std::string const &window_name, Vec2 const &size);
    float GetAspectRatio() final;
    bool ShouldQuit() final;
    void *GetHandler() final;
    void Close() final;
    void SwapFrame() final;

private:
    SDL_Window *sdl_handler_{nullptr};
    Vec2 size_{1280, 720};
    bool should_quit_{false};
};