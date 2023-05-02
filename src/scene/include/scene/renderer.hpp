#pragma once

#include "definitions.hpp"
#include "shader.hpp"
#include "scene.hpp"
#include "geometry/mesh.hpp"
#include "utils/camera.hpp"
#include "opengl.hpp"
#include "lines.hpp"
#include "glm/mat4x4.hpp"

namespace scene
{
    class GEODIP_API Renderer
    {
    public:
        struct Opts
        {
            glm::mat4x4 model_view_;
            glm::vec3 color_;
            SceneID id_;
        };

        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;

        Renderer(Renderer &&) = delete;
        Renderer &operator=(Renderer &&) = delete;

        static Renderer &Get();
        void Mesh(gl::Mesh &mesh, Opts const &opts);
        void Lines(gl::Lines &mesh, const glm::mat4x4 &view);
        static void Setup(const std::shared_ptr<Opengl> &gl,
                          std::shared_ptr<Camera> const &camera);

        void Clear();

    private:
        Renderer();

        static inline scene::Renderer *instance_;

        std::shared_ptr<Opengl> gl_;
        std::shared_ptr<Camera> camera_;

        Shader mesh_shader_, lines_shader_;
    };
}