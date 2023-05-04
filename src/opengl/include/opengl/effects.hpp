#pragma once

#include "opengl/shader.hpp"
#include "opengl/framebuffer.hpp"

class Effects
{
public:
    Effects();
    void Outline(Framebuffer const &from, Framebuffer const &to);

private:
    GLuint vao_;
    Shader outline_shader_{shaders::kEffectsShader,
                           shaders::kOutlineFragmentShader};
};