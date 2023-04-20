#include "tex2D.hpp"

Tex2D::Tex2D(std::string path)
{
    glGenTextures(1, &id_);
    info("Creating texture with id %d", id_);
    stbi_set_flip_vertically_on_load(1);
    unsigned char *img{stbi_load(path.c_str(), &w_, &h_, &number_of_comp_, 0)};
    if (!img)
    {
        warn("Failed to create texture with id %d", id_);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, id_);
        if (path.substr(path.size() - 3) == "png")
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w_, h_, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w_, h_, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    stbi_image_free(img);
}