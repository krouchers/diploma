#include "scene/renderer.hpp"

#include <memory>

namespace scene
{
    Renderer::Renderer()
        : mesh_shader_{shaders::kVertexShader, shaders::kFragmentShader}
    {
    }

    Renderer &Renderer::Get()
    {
        return *instance_;
    }

    void Renderer::Mesh(gl::Mesh &mesh, const Mat4x4 &view)
    {
        mesh_shader_.Bind();
        mesh_shader_.Set("tex1", 0);
        mesh_shader_.Set("tex2", 1);
        mesh_shader_.Set("transform", projection_ * view);
        mesh.Render();
    }

    void Renderer::SetProjectionMatrix(const Mat4x4 &proj)
    {
        projection_ = proj;
    }

    void Renderer::Setup(std::shared_ptr<IWindow> win, const Camera &cam)
    {
        auto gl_ = std::unique_ptr<Opengl>(new Opengl{win, cam});
        instance_ = new Renderer{};
        instance_->gl_ = std::move(gl_);
    }

    void Renderer::Render3D(Scene &scene, Camera &cam)
    {
        scene.ForItems([&](scene::Item &item)
                       { item.Render(cam.GetView()); });
    }
}