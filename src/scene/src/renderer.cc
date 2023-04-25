#include "scene/renderer.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace scene
{
    Renderer::Renderer()
        : mesh_shader_{shaders::kMeshVertexShader, shaders::kMeshFragmentShader},
          lines_shader_{shaders::kLinesVertexShader, shaders::kLinesFragmentShader}
    {
    }

    void Renderer::Mesh(gl::Mesh &mesh, const glm::mat4x4 &view)
    {
        mesh_shader_.Bind();
        mesh_shader_.Set("transform", view);
        mesh.Render();
    }

    void Renderer::Clear()
    {
        glClearColor(50.f / 255.f, 58.f / 255.f, 58.f / 255.f, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::Setup(const std::shared_ptr<Opengl> &gl)
    {
        instance_ = new scene::Renderer{};
        instance_->gl_ = gl;
    }

    scene::Renderer &Renderer::Get()
    {
        return *instance_;
    }

    void Renderer::Lines(gl::Lines &lines, const glm::mat4x4 &view)
    {
        lines_shader_.Bind();
        lines_shader_.Set("mvp", view);
        lines.Render();
    }
}
