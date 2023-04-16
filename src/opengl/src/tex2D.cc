#include "tex2D.hpp"


tex2D::tex2D(std::string path)
{
    glGenTextures(1, &m_id);
    info("Creating texture with id %d", m_id);
    stbi_set_flip_vertically_on_load(1);
    unsigned char *img{stbi_load(path.c_str(), &m_w, &m_h, &m_number_of_comp, 0)};
    if (!img)
    {
        warn("Failed to create texture with id %d", m_id);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
        if (path.substr(path.size() - 3) == "png")
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_w, m_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_w, m_h, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    stbi_image_free(img);
}