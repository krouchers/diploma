#pragma once

#include <memory>
#include <string>

#include "SDL.h"
#include "shader.hpp"

class window;

class graphic
{
public:
    graphic(const window &);
    ~graphic();
    graphic(const graphic &) = delete;
    graphic &operator=(const graphic &) = delete;

    void render();
private:
    SDL_GLContext gl_context_;
    void setup_debug_proc();
    std::string version();
    shader shader_;
    GLuint VAO;
};