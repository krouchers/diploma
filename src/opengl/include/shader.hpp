#pragma once
#include "glm/mat4x4.hpp"

#include <string>

namespace shaders
{
    inline const std::string kVertexShader{
        R"(#version 410 core
        layout(location = 0) in vec3 vec_pos;
        layout(location = 1) in vec3 vec_col;
        layout(location = 2) in vec2 t_coord_in;

        out vec2 t_coord;
        uniform mat4 transform;

        void main(){
            gl_Position = transform * vec4(vec_pos, 1.0);
            t_coord = t_coord_in;
        }
        )"};
    inline const std::string kFragmentShader{
        R"(#version 410 core
        in vec2 t_coord;
        out vec4 out_color;
        
        uniform sampler2D tex1;
        uniform sampler2D tex2;
        
        void main(){
            out_color = texture(tex1, t_coord);
        }
        )"};
}

#include <string>

#include "glad.hpp"

class Shader
{
public:
    Shader(const std::string &vertex, const std::string &fragment);
    /**
     * @brief Компилирует vertex и fragment шайдеры.
     *
     * @param vertex Строка содержащая исходный код vertex шейдера.
     * @param fragment Строка содержащая исходный код fragment шейдера.
     */
    void Load(const std::string vertex, const std::string fragment);
    /**
     * @brief Обновляет значение юниформ переменной шейдера.
     *
     * @param uniform_name Имя юниформ переменной.
     * @param value Привсваемое ей значение.
     * @return true - если значение успешно обновлено.
     * @return false - если значение обновыить не вышло, в случае если переменной
     * с таким именем нет, или она была соптимизирована glsl компилятором.
     */
    void Set(const char *uniform_name, float value);
    /**
     * @brief Обновляет значение юниформ объекта формата "одно целочисленное".
     *
     * @param uniform_name Имя юниформ переменной.
     * @param value Привсваемое ей значение.
     */
    void Set(const char *uniform_name, int value);

    /**
     * @brief Обновляет значение юниформ объекта формата "матрица".
     *
     * @param uniform_name Имя юниформ переменной.
     * @param value Привсваемое ей значение.
     */
    void Set(const char *uniform_name, const glm::mat4x4 &value);

    inline GLuint GetProgramId() const noexcept { return program_; };
    inline void Bind() { glUseProgram(program_); }

    ~Shader();

private:
    /**
     * @brief Проверить статус компиляции.
     *
     * @param shader Шейдер, который нужно проверить.
     * @return true
     * @return false
     */
    bool Validate(GLuint shader);
    GLuint vertex_{0}, fragment_{0}, program_{0};
};