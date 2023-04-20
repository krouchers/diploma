#include "scene/renderer.hpp"

#include <memory>

namespace scene
{
    Renderer::Renderer()
        : mesh_shader_{shaders::kVertexShader, shaders::kFragmentShader}
    {
    }

    void Renderer::Mesh(gl::Mesh &mesh, const Mat4x4 &view)
    {
        mesh_shader_.Bind();
        mesh_shader_.Set("transform", view);
        mesh.Render();
    }

    void Renderer::Render3D(Scene &scene, Camera &cam)
    {
        scene.ForItems([&](scene::Item &item)
                       { item.Render(cam.GetProjection()); });
    }

    void Renderer::Clear()
    {
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::Setup(const std::shared_ptr<Opengl> &gl)
    {
        instance_ = std::unique_ptr<scene::Renderer>(new scene::Renderer{});
        instance_->gl_ = gl;
    }

    scene::Renderer &Renderer::Get()
    {
        return *instance_;
    }
}
