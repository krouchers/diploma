#pragma once

#include <vector>

#include "math.hpp"
#include "glad.hpp"

struct vert
{
    vec3 pos;
    vec3 norm;
    vec2 tex_coord;
};

class mesh
{
public:

    mesh() = default;
    /**
     * @brief Construct a new mesh object
     *
     * @param vertices Vertices vector
     * @param indices  Indexes vector
     */
    mesh(std::vector<vert> &&vertices, std::vector<GLuint> &&indices);
    /**
     * @brief Вызывает openGL draw функцию 
     * 
     */
    void render();

private:
    /**
     * @brief Set the up opengl vao
     *
     */
    void setup_vao();

    GLuint vao_, vbo_, veo_;
    std::vector<vert> vertices_;
    std::vector<GLuint> indices_;
};