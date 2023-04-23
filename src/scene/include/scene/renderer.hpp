#pragma once

#include "shader.hpp"
#include "math.hpp"
#include "scene.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "opengl.hpp"

namespace scene
{
    class Renderer
    {
    public:
        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;

        Renderer(Renderer &&) = delete;
        Renderer &operator=(Renderer &&) = delete;

        static Renderer &Get();
        void Mesh(gl::Mesh &mesh, const glm::mat4x4 &view);
        void SetProjectionMatrix(const Mat4x4 &proj);
        static void Setup(const std::shared_ptr<Opengl> &gl);
        void Render3D(Scene &, Camera &);

        void Clear();

    private:
        Renderer();

        static inline std::unique_ptr<scene::Renderer> instance_;

        std::shared_ptr<Opengl> gl_;

        Shader mesh_shader_;
    };
}