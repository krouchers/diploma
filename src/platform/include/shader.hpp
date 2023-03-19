#pragma once

#include <string>

namespace shaders
{
    const std::string vertex_shader{
        R"(#version 410 core
        layout(location = 0) in vec3 vec_pos;
        layout(location = 1) in vec3 vec_col;
        layout(location = 2) in vec2 t_coord_in;

        out vec2 t_coord;

        void main(){
            gl_Position.xyz = vec_pos;
            gl_Position.w = 1.0;
            t_coord = t_coord_in;
        }
        )"};
    const std::string fragment_shader{
        R"(#version 410 core
        in vec2 t_coord;
        out vec4 out_color;
        
        uniform sampler2D tex1;
        uniform sampler2D tex2;
        
        void main(){
            out_color = mix(texture(tex1, t_coord),texture(tex2, t_coord), 0.2);
        }
        )"};
}

#include <string>

#include "glad.hpp"

class shader
{
public:
    /**
     * @brief Компилирует vertex и fragment шайдеры.
     *
     * @param vertex Строка содержащая исходный код vertex шейдера.
     * @param fragment Строка содержащая исходный код fragment шейдера.
     */
    void load(const std::string vertex, const std::string fragment);
    /**
     * @brief Обновляет значение юниформ переменной шейдера.
     *
     * @param uniform_name Имя юниформ переменной.
     * @param value Привсваемое ей значение.
     * @return true - если значение успешно обновлено.
     * @return false - если значение обновыить не вышло, в случае если переменной
     * с таким именем нет, или она была соптимизирована glsl компилятором.
     */
    void set(const char *uniform_name, float value);
    /**
     * @brief Обновляет значение юниформ объекта формата "одно целочисленное".
     *
     * @param uniform_name Имя юниформ переменной.
     * @param value Привсваемое ей значение.
     * @return true - если значение успешно обновлено.
     * @return false - если значение обновыить не вышло, в случае если переменной
     * с таким именем нет, или она была соптимизирована glsl компилятором.
     */
    void set(const char *uniform_name, int value);

    inline GLuint get_program_id() const noexcept { return program_; };
    inline void bind() { glUseProgram(program_); }

    ~shader();

private:
    /**
     * @brief Проверить статус компиляции.
     *
     * @param shader Шейдер, который нужно проверить.
     * @return true
     * @return false
     */
    bool validate(GLuint shader);
    GLuint vertex_{0}, fragment_{0}, program_{0};
};