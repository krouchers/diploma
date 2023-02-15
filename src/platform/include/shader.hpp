#pragma once

#include <string>

namespace shaders
{
    const std::string vertex_shader{
        R"(#version 330 core
        layout(location = 0) in vec3 vec_pos;
        void main(){
            gl_Position.xyz = vec_pos;
            gl_Position.w = 1.0;
        }
        )"};
    const std::string fragment_shader{
        R"(#version 330 core
        out vec3 color;
        void main(){
            color = vec3(1, 0, 0);
        }
        )"};
}

#include <string>

#include "glad.hpp"

class shader
{
public:
    void load(const std::string vertex, const std::string fragment);
    inline GLuint get_program_id() const noexcept { return program_; };

private:
    bool validate(GLuint shader);
    GLuint vertex_{0}, fragment_{0}, program_{0};
};