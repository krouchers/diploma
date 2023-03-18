#pragma once

#include "glad.hpp"
#include "log.hpp"

#include "stb_loader.hpp"

#include <string>

class tex2D
{
public:
    tex2D() = default;
    /**
     * @brief Инициализирует текстуру
     *
     * @param path Путь к текстуре
     */
    tex2D(std::string path)
    {
        glGenTextures(1, &m_id);
        info("Creating texture with id %d", m_id);
        unsigned char *img{stbi_load(path.c_str(), &m_w, &m_h, &m_number_of_comp, 0)};
        if (!img)
        {
            warn("Failed to create texture with id %d", m_id);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, m_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_w, m_h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        stbi_image_free(img);
    }

    // FIXME: Shouldn't pass program id
    void
    bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

private:
    GLuint m_id;
    int m_w, m_h, m_number_of_comp;
};