#include "scene/renderer.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "common/colors.hpp"

#include <memory>

namespace scene
{
    Renderer::Renderer()
        : mesh_shader_{shaders::kMeshVertexShader, shaders::kMeshFragmentShader},
          lines_shader_{shaders::kLinesVertexShader, shaders::kLinesFragmentShader},
          outline_shader_{shaders::kLinesVertexShader, shaders::kLinesFragmentShader},
          instanced_shader_{shaders::kInstancedVertex, shaders::kMeshFragmentShader},
          framebuffer_{2}, id_resolve_{1}
    {
    }

    void Renderer::Mesh(geometry::Mesh &mesh, const MeshOpts &opts)
    {
        mesh_shader_.Bind();
        mesh_shader_.Set("mv", camera_->GetView() * opts.pose_);
        mesh_shader_.Set("p", camera_->GetProjection());
        mesh_shader_.Set("select_id", opts.sel_id_);
        mesh_shader_.Set("hover_id", opts.hov_id_);
        mesh_shader_.Set("color", opts.color_);
        mesh_shader_.Set("select_color", Color::outline);
        mesh_shader_.Set("hover_color", Color::hover);
        mesh_shader_.Set("use_f_id", opts.use_f_id);
        if (opts.depth_only)
            gl::ColorOutput(false);
        mesh.Render();
        if (opts.depth_only)
            gl::ColorOutput(true);
    }

    void Renderer::Clear()
    {
        framebuffer_.Clear();
        id_resolve_.Clear();
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

    void Renderer::Begin()
    {
        framebuffer_.Bind();
    }

    void Renderer::Complete()
    {
        framebuffer_.BlitToScreen();
        framebuffer_.BlitTo(id_resolve_, 1);
    }

    SceneID Renderer::ReadID(glm::vec2 const &pos)
    {
        int x = pos.x;
        int y = 720 - pos.y + 1;
        auto id = id_resolve_.ReadAt({x, y});
        return id[0];
    }

    void Renderer::Outline(scene::Item &item)
    {
        framebuffer_.ClearDepth();
        item.Render(true);
        effects_.Outline(framebuffer_, framebuffer_);
    }

    void Renderer::ClearDepth()
    {
        framebuffer_.ClearDepth();
    }

    glm::vec3 Renderer::GetCameraPos()
    {
        return camera_->GetPosition();
    }

    void Renderer::Halfedge(HalfedgeOpts const &opts)
    {
        auto &[faces, spheres] = opts.shapes_;
        MeshOpts m_opts;
        m_opts.pose_ = glm::mat4x4(1.0f);
        m_opts.color_ = Color::white;
        m_opts.use_f_id = true;
        m_opts.hov_id_ = opts.hov_id_;
        m_opts.sel_id_ = opts.sel_id_;
        Renderer::Mesh(faces, m_opts);

        instanced_shader_.Bind();
        instanced_shader_.Set("p", camera_->GetProjection());
        instanced_shader_.Set("mv", camera_->GetView());
        instanced_shader_.Set("color", Color::white);
        instanced_shader_.Set("select_color", Color::outline);
        instanced_shader_.Set("hover_color", Color::hover);
        instanced_shader_.Set("use_f_id", true);
        spheres.Render();
        }
}
