#pragma once

#include <string>

namespace shaders
{
    inline const std::string vertex_shader{R"(
    )"};
    inline const std::string fragment_shader{R"(
    )"};
}

#include <string>

#include "glad.hpp"

class shader
{
public:
    void load(const std::string vertex, const std::string fragment);

private:
    bool validate(GLuint shader);
    GLuint vertex_ = 0, fragment_ = 0;
};