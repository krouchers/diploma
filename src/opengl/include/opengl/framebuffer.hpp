#pragma once

#include "glad.hpp"
#include "glm/vec2.hpp"

#include <vector>
#include <array>

class Framebuffer
{
public:
    Framebuffer(unsigned count_of_textures);
    void Bind() const;
    void Clear();
    void ClearDepth();
    void BlitTo(Framebuffer to, GLuint buf);
    void BlitToScreen();
    GLuint GetDepth() const;
    std::array<GLubyte, 4> ReadAt(glm::vec2 const &pos);
    GLuint GetID()
    {
        return framebuffer_;
    };

private:
    GLuint framebuffer_, depth_;

    /**
     * @brief vector of textures to draw into.
     *
     */
    std::vector<GLuint> textures_;
};