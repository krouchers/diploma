#include "framebuffer.hpp"
#include "utils/log.hpp"

#include <stdexcept>

framebuffer::framebuffer(unsigned count_of_textures)
{
    info("Creating framebuffer");
    
    m_out_textures.resize(count_of_textures);

    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

    glGenTextures(m_out_textures.size(), m_out_textures.data());

    for (unsigned i{0}; i < m_out_textures.size(); ++i)
    {
        glBindTexture(GL_TEXTURE_2D, m_out_textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_out_textures[i], 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    if (!glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::runtime_error("Frame buffer is not complete");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}