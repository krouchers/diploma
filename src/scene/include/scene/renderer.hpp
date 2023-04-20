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
        void Mesh(gl::Mesh &mesh, const Mat4x4 &view);
        void SetProjectionMatrix(const Mat4x4 &proj);
        static void Setup(std::shared_ptr<IWindow> win, const Camera &cam);
        void Render3D(Scene &, Camera &);

    private:
        Renderer();

        static inline Renderer *instance_{nullptr};

        Shader mesh_shader_;

        Mat4x4 projection_;

        std::unique_ptr<Opengl> gl_{};
    };
}