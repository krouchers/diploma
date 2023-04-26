#pragma once

#include "glad.hpp"
#include "utils/log.hpp"

#include <string>

class Tex2D
{
public:
    Tex2D() = default;
    /**
     * @brief Инициализирует текстуру
     *
     * @param path Путь к текстуре
     */
    explicit Tex2D(std::string path);

    // FIXME: Shouldn't pass program id
    void Bind(int idx)
    {
        glActiveTexture(GL_TEXTURE0 + idx);
        glBindTexture(GL_TEXTURE_2D, id_);
    }

private:
    GLuint id_;
    int w_, h_, number_of_comp_;
};