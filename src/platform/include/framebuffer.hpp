#pragma once

#include "glad.hpp"

#include <vector>

class framebuffer
{
public:
    framebuffer(unsigned count_of_textures);

private:
    GLuint m_framebuffer, m_rbo;

    /**
     * @brief vector of textures to draw into.
     * 
     */
    std::vector<GLuint> m_out_textures;
};