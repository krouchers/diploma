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

    void Renderer::Mesh(gl::Mesh &mesh, const Opts &opts)
    {
        mesh_shader_.Bind();
        mesh_shader_.Set("mv", opts.model_view_);
        mesh_shader_.Set("p", camera_->GetProjection());
        mesh_shader_.Set("color", opts.color_);
        mesh_shader_.Set("light_pos", camera_->GetPosition());
        mesh.Render();
    }

    void Renderer::Clear()
    {
        glClearColor(50.f / 255.f, 58.f / 255.f, 58.f / 255.f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::Setup(const std::shared_ptr<Opengl> &gl,
                         std::shared_ptr<Camera> const &camera)
    {
        instance_ = new scene::Renderer{};
        instance_->gl_ = gl;
        instance_->camera_ = camera;
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
