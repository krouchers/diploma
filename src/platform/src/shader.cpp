#include "shader.hpp"
#include "log.hpp"

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
}

bool shader::validate(GLuint shader)
{
    GLint is_compiled{0};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    return is_compiled == GL_TRUE;
    if (!is_compiled)
    {
        GLint len{0};
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        char *msg{new char[len]};
        glGetShaderInfoLog(shader, len, nullptr, msg);
        warn("Failed to compile %s shader: %s", shader, msg);
    }
}