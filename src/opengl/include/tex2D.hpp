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
    tex2D(std::string path);

    // FIXME: Shouldn't pass program id
    void bind(int idx)
    {
        glActiveTexture(GL_TEXTURE0 + idx);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

private:
    GLuint m_id;
    int m_w, m_h, m_number_of_comp;
};