#include "shader.hpp"
#include "log.hpp"

#include <cmath>

void shader::load(const std::string vertex, const std::string fragment)
{
    vertex_ = glCreateShader(GL_VERTEX_SHADER);
    fragment_ = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *v = vertex.c_str();
    const GLchar *f = fragment.c_str();
    glShaderSource(vertex_, 1, &v, nullptr);
    glShaderSource(fragment_, 1, &f, nullptr);

    glCompileShader(vertex_);
    glCompileShader(fragment_);

    validate(vertex_);
    validate(fragment_);

    program_ = glCreateProgram();
    glAttachShader(program_, vertex_);
    glAttachShader(program_, fragment_);
    glLinkProgram(program_);
    GLint status;
    glGetProgramiv(program_, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        warn("Failed to link program");
        GLchar buf[128];
        glGetProgramInfoLog(program_, sizeof(buf), nullptr, buf);
        warn("%s", buf);
    }
}

bool shader::validate(GLuint shader)
{
    GLint is_compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled != GL_TRUE)
    {
        GLint len{0};
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        char *msg{new char[len]};
        glGetShaderInfoLog(shader, len, nullptr, msg);
        warn("Failed to compile %d shader: %s", shader, msg);
    }
    return is_compiled == GL_TRUE;
}

bool shader::update_unifom(const char *uniform_name, float value)
{
    // FIXME: should be better logic
    auto location{glGetUniformLocation(program_, uniform_name)};
    if (location == -1)
    {
        return false;
    }
    glUniform4f(location, 0, value, 0, 1);
    return true;
}

shader::~shader()
{
    glDeleteShader(fragment_);
    glDeleteShader(vertex_);
    glDeleteProgram(program_);
}