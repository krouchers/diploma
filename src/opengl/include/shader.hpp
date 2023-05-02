#pragma once
#include "glm/mat4x4.hpp"

#include <string>

namespace shaders
{
    inline const std::string kMeshVertexShader{
        R"(#version 410 core
        layout(location = 0) in vec3 vec_pos;
        layout(location = 1) in vec3 vec_norm;

        out vec3 f_norm;
        uniform mat4 mv;
        uniform mat4 p;

        void main(){
            gl_Position = p * mv * vec4(vec_pos, 1.0);
            f_norm = (mv * vec4(vec_norm, 0.0f)).xyz;
        }
        )"};
    inline const std::string kMeshFragmentShader{
        R"(#version 410 core
        out vec4 out_color;
        in vec3 f_norm;
        uniform vec3 color;
        
        void main(){
            float ndotl = abs(f_norm.z);
            float diffuse = max(ndotl, 0.4f);
            out_color = diffuse * vec4(color, 1.0f);
        }
        )"};

    inline const std::string kLinesVertexShader{
        R"(#version 410 core
        layout(location = 0) in vec3 vec_pos;
        layout(location = 1) in vec3 vec_col;

        in vec3 f_light;
        out vec4 f_col;
        uniform mat4 mvp;

        void main(){
            gl_Position = mvp * vec4(vec_pos, 1.0);
            f_col = vec4(vec_col, 1.0);
        }
        )"};
    inline const std::string kLinesFragmentShader{
        R"(#version 410 core
        in vec4 f_col;
        out vec4 out_color;
        
        void main(){
            out_color = f_col;
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

    void Set(const char *uniform_name, glm::vec3 const &value);

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