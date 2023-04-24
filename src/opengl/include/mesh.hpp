#pragma once

#include <vector>
#include "math/vec3.hpp"
#include "math/vec2.hpp"

#include "glad.hpp"

struct Vert
{
    math::Vec3 pos;
    math::Vec3 norm;
    math::Vec2 tex_coord;
};

namespace gl
{
    class Mesh
    {
    public:
        Mesh() = default;
        /**
         * @brief Construct a new Mesh object
         *
         * @param vertices Vertices vector
         * @param indices  Indexes vector
         */
        Mesh(std::vector<Vert> &&vertices, std::vector<GLuint> &&indices);
        /**
         * @brief Вызывает openGL draw функцию
         *
         */
        void Render();

    private:
        /**
         * @brief Set the up opengl vao
         *
         */
        void SetupVao();

        GLuint vao_, vbo_, veo_;
        std::vector<Vert> vertices_;
        std::vector<GLuint> indices_;
    };
}