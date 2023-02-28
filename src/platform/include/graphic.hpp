#pragma once

#include <memory>
#include <string>

#include "SDL.h"
#include "shader.hpp"

class window;

class graphic
{
public:
    graphic(const std::shared_ptr<window>);
    ~graphic();
    graphic(const graphic &) = delete;
    graphic &operator=(const graphic &) = delete;

    void render();

private:
    void setup_debug_proc();

    std::shared_ptr<window> window_;
    SDL_GLContext gl_context_;
    std::string version();
    shader shader_;
    GLuint VAO_, VBO_, EBO_;
};