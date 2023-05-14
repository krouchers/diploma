#include "opengl/shader.hpp"
#include "utils/log.hpp"

#include "glm/mat4x4.hpp"

#include <cmath>

Shader::Shader(const std::string &vertex, const std::string &fragment)
{
    Load(vertex, fragment);
}

void Shader::Load(const std::string vertex, const std::string fragment)
{
    vertex_ = glCreateShader(GL_VERTEX_SHADER);
    fragment_ = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar *v = vertex.c_str();
    const GLchar *f = fragment.c_str();
    glShaderSource(vertex_, 1, &v, nullptr);
    glShaderSource(fragment_, 1, &f, nullptr);

    glCompileShader(vertex_);
    glCompileShader(fragment_);

    Validate(vertex_);
    Validate(fragment_);

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

bool Shader::Validate(GLuint shader_id)
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

void Shader::Set(const char *uniform_name, float value) const
{
    // FIXME: should be better logic
    glUniform4f(glGetUniformLocation(program_, uniform_name), 0, value, 0, 1);
}

void Shader::Set(const char *uniform_name, int value) const
{
    Bind();
    glUniform1i(glGetUniformLocation(program_, uniform_name), value);
}

void Shader::Set(const char *uniform_name, unsigned int value) const
{
    Bind();
    glUniform1ui(glGetUniformLocation(program_, uniform_name), value);
}

void Shader::Set(const char *uniform_name, glm::vec3 const &value) const
{
    Bind();
    glUniform3fv(glGetUniformLocation(program_, uniform_name), 1, &value[0]);
}

void Shader::Set(const char *uniform_name, glm::vec2 const &value) const
{
    Bind();
    glUniform2fv(glGetUniformLocation(program_, uniform_name), 1, &value[0]);
}

void Shader::Set(const char *uniform_name, const glm::mat4x4 &value) const
{
    Bind();
    auto id = glGetUniformLocation(program_, uniform_name);
    if (id == GL_INVALID_VALUE or id == GL_INVALID_OPERATION)
    {
        warn("Failed to pass matrix to Shader");
    }
    // glUniformMatrix4fv(glGetUniformLocation(program_, uniform_name), 1, GL_FALSE, value.data);
    glUniformMatrix4fv(id, 1, GL_FALSE, &value[0][0]);
}

Shader::~Shader()
{
    glDeleteShader(fragment_);
    glDeleteShader(vertex_);
    glDeleteProgram(program_);
}
namespace shaders
{
    inline const std::string kMeshVertexShader{
        R"(#version 330 core
        layout(location = 0) in vec3 v_pos;
        layout(location = 1) in vec3 v_norm;
        layout(location = 2) in int v_id;

        out vec3 f_norm;
        out uint f_id;

        uniform mat4 mv;
        uniform mat4 p;

        void main(){
            gl_Position = p * mv * vec4(v_pos, 1.0);
            f_norm = (mv * vec4(v_norm, 0.0f)).xyz;
            f_id = v_id;
        }
        )"};
    inline const std::string kMeshFragmentShader{
        R"(#version 330 core
        layout(location = 0) out vec4 out_color;
        layout(location = 1) out vec4 out_id;

        in vec3 f_norm;
        flat in uint f_id;

        uniform vec3 color, hover_color, select_color;
        uniform uint select_id, hover_id;
        uniform bool use_f_id;
        
        void main(){
            float ndotl = abs(f_norm.z);
            float diffuse = max(ndotl, 0.4f);
            out_color = vec4(diffuse * color, 1.0f);
            if(use_f_id){
                out_id = vec4((f_id & 0xFFu) / 255.0f, 0.0f, 0.0f, 1.0f);
                if(f_id == select_id)
                    out_color = vec4(diffuse * select_color, 1.0f);
                else if(f_id == hover_id)
                    out_color = vec4(diffuse * hover_color, 1.0f);
                else 
                    out_color = vec4(diffuse * color, 1.0f);
            } else {
                out_id = vec4((select_id & 0xFFu) / 255.0f, 0.0f, 0.0f, 1.0f);
                out_color = vec4(diffuse * color, 1.0f);
            }
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

    inline const std::string kEffectsShader{
        R"(#version 410 core

        uniform vec2 bound[4] = vec2[](vec2(-1.0f, 1.0f),
        vec2(-1.0f, -1.0f), vec2(1.0f, 1.0f), vec2(1.0f, -1.0f));
        
        void main(){
            gl_Position = vec4(bound[gl_VertexID], 1.0f, 1.0f);
        }
        )"};
    inline const std::string kOutlineFragmentShader{
        R"(#version 410 core
        out vec4 out_color;

        uniform sampler2D depth;
        uniform vec2 icoord;
        uniform vec3 color;

        void main(){
            vec2 coord = gl_FragCoord.xy;
            float o = texture(depth, icoord * coord).r;
            
            float max_depth = 0.0f;
            for(int i = -2; i < 2; ++i)
                for(int j = -2; j < 2; ++j){
                    max_depth = max(texture(depth, icoord * (coord + vec2(i, j))).r, max_depth);
                }
            float a = (o != 1.0f && max_depth == 1.0f ?  1.0f : 0.0f);
            out_color = vec4(color, a);
        }
        )"};

    inline const std::string kInstancedVertex{
        R"(#version 330 core
        layout(location = 0) in vec3 v_pos;
        layout(location = 1) in vec3 v_norm;
        layout(location = 2) in uint v_id;

        layout(location = 3) in uint i_id;
        layout(location = 4) in mat4 i_transform;

        out vec3 f_norm;
        out uint f_id;

        uniform mat4 mv;
        uniform mat4 p;

        void main(){
            gl_Position = p * mv * i_transform * vec4(v_pos, 1.0f);
            f_norm = (mv * i_transform * vec4(v_norm, 0.0f)).xyz;
            f_id = i_id;
        }
        )"};
}