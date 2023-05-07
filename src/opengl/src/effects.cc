#include "opengl/effects.hpp"
#include "glm/vec2.hpp"
#include "colors.hpp"

void Effects::Outline(Framebuffer const &from, Framebuffer const &to)
{
    glFlush();
    outline_shader_.Bind();
    to.Bind();
    glBindTexture(GL_TEXTURE_2D, from.GetDepth());
    outline_shader_.Set("icoord", 1.0f / glm::vec2{1280.0f, 720.0f});
    outline_shader_.Set("color", Color::outline);
    outline_shader_.Set("depth", 0);

    glBindVertexArray(vao_);
    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(0);
}

Effects::Effects()
{
    glGenVertexArrays(1, &vao_);
}