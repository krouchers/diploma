#pragma once
#include <iostream>
#include <exception>
#include <optional>

#include "definitions.hpp"
#include "interfaces/window.hpp"
#include "SDL.h"
#include "utils/log.hpp"

class GEODIP_API SdlWindow : public IWindow
{
public:
    SdlWindow(std::string const &window_name, glm::vec2 const &size);
    float GetAspectRatio() final;
    bool ShouldQuit() final;
    void *GetHandler() final;
    void Close() final;
    void SwapFrame() final;
    glm::vec2 GetSize() final;
    virtual ~SdlWindow() = default;

private:
    SDL_Window *sdl_handler_{nullptr};
    glm::vec2 size_{1280, 720};
    bool should_quit_{false};
};