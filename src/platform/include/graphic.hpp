#pragma once
#include "SDL.h"

class window;

class graphic
{
public:
    graphic(const window &);
    ~graphic();
    graphic(const graphic &) = delete;
    graphic &operator=(const graphic &) = delete;

private:
    SDL_GLContext *gl_context_ = nullptr;
};