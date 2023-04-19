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

bool shader::validate(GLuint shader_id)
{
    GLint is_compiled;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled != GL_TRUE)
    {
        GLint len{0};
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
        char *msg{new char[len]};
        glGetShaderInfoLog(shader_id, len, nullptr, msg);
        warn("Failed to compile %d shader: %s", shader_id, msg);
    }
    return is_compiled == GL_TRUE;
}

void shader::set(const char *uniform_name, float value)
{
    // FIXME: should be better logic
    glUniform4f(glGetUniformLocation(program_, uniform_name), 0, value, 0, 1);
}

void shader::set(const char *uniform_name, int value)
{
    bind();
    glUniform1i(glGetUniformLocation(program_, uniform_name), value);
}

void shader::set(const char *uniform_name, const mat4x4 &value)
{
    bind();
    auto id = glGetUniformLocation(program_, uniform_name);
    if(id == GL_INVALID_VALUE or id == GL_INVALID_OPERATION){
        warn("Failed to pass matrix to shader");
    }
    // glUniformMatrix4fv(glGetUniformLocation(program_, uniform_name), 1, GL_FALSE, value.data);
    glUniformMatrix4fv(id, 1, GL_FALSE, value.data);
}

shader::~shader()
{
    glDeleteShader(fragment_);
    glDeleteShader(vertex_);
    glDeleteProgram(program_);
}