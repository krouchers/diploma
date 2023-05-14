#pragma once
#include "glm/mat4x4.hpp"

#include <string>

namespace shaders
{
    extern const std::string kMeshVertexShader;
    extern const std::string kMeshFragmentShader;

    extern const std::string kLinesVertexShader;
    extern const std::string kLinesFragmentShader;

    extern const std::string kEffectsShader;
    extern const std::string kOutlineFragmentShader;

    extern const std::string kInstancedVertex;
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
    void Set(const char *uniform_name, float value) const;
    /**
     * @brief Обновляет значение юниформ объекта формата "одно целочисленное".
     *
     * @param uniform_name Имя юниформ переменной.
     * @param value Привсваемое ей значение.
     */
    void Set(const char *uniform_name, int value) const;

    void Set(const char *uniform_name, unsigned int value) const;

    void Set(const char *uniform_name, glm::vec3 const &value) const;

    void Set(const char *uniform_name, glm::vec2 const &value) const;

    /**
     * @brief Обновляет значение юниформ объекта формата "матрица".
     *
     * @param uniform_name Имя юниформ переменной.
     * @param value Привсваемое ей значение.
     */
    void Set(const char *uniform_name, const glm::mat4x4 &value) const;

    inline GLuint GetProgramId() const noexcept { return program_; };
    inline void Bind() const { glUseProgram(program_); }

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