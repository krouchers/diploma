#include "opengl/framebuffer.hpp"
#include "utils/log.hpp"

#include <stdexcept>

Framebuffer::Framebuffer(unsigned count_of_textures)
{
    info("Creating framebuffer");

    textures_.resize(count_of_textures);

    glGenFramebuffers(1, &framebuffer_);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);

    glGenTextures(textures_.size(), textures_.data());

    std::vector<GLuint> draw_buffers;
    for (unsigned i{0}; i < textures_.size(); ++i)
    {
        glBindTexture(GL_TEXTURE_2D, textures_[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures_[i], 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        draw_buffers.push_back(GL_COLOR_ATTACHMENT0 + i);
    }

    glGenTextures(1, &depth_);
    glBindTexture(GL_TEXTURE_2D, depth_);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, 1280, 720, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDrawBuffers(draw_buffers.size(), draw_buffers.data());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
}

void Framebuffer::Clear()
{
    Bind();
    float color[]{50.f / 255.f, 58.f / 255.f, 58.f / 255.f, 1.0f};
    float id[]{0.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, color);
    glClearBufferfv(GL_COLOR, 1, id);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Framebuffer::BlitTo(Framebuffer to, GLuint buf)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer_);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, to.GetID());
    glReadBuffer(GL_COLOR_ATTACHMENT0 + buf);
    glBlitFramebuffer(0, 0, 1280, 720, 0, 0, 1280, 720, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::BlitToScreen()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer_);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glBlitFramebuffer(0, 0, 1280, 720, 0, 0, 1280, 720, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

std::array<GLubyte, 4> Framebuffer::ReadAt(const glm::vec2 &pos)
{
    std::array<GLubyte, 4> data;
    glGetTextureSubImage(textures_[0], 0, pos.x, pos.y, 0, 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, sizeof(data), data.data());
    return data;
}

GLuint Framebuffer::GetDepth() const
{
    return depth_;
}

void Framebuffer::ClearDepth()
{
    Bind();
    glClear(GL_DEPTH_BUFFER_BIT);
}