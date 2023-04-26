#pragma once

#include "shader.hpp"
#include "scene.hpp"
#include "mesh.hpp"
#include "utils/camera.hpp"
#include "opengl.hpp"
#include "lines.hpp"

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
        void Lines(gl::Lines &mesh, const glm::mat4x4 &view);
        static void Setup(const std::shared_ptr<Opengl> &gl);

        void Clear();

    private:
        Renderer();

        static inline scene::Renderer *instance_;

        std::shared_ptr<Opengl> gl_;

        Shader mesh_shader_, lines_shader_;
    };
}