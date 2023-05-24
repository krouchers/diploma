#pragma once

#include "definitions.hpp"
#include "scene.hpp"
#include "geometry/mesh.hpp"
#include "geometry/halfedge_mesh.hpp"
#include "utils/camera.hpp"

#include "opengl/shader.hpp"
#include "opengl/opengl.hpp"
#include "opengl/framebuffer.hpp"
#include "opengl/lines.hpp"
#include "opengl/effects.hpp"
#include "opengl/instance.hpp"

#include "glm/mat4x4.hpp"

namespace scene
{
    class GEODIP_API Renderer
    {
    public:
        struct MeshOpts
        {
            glm::mat4x4 pose_;
            glm::vec3 color_;
            SceneID sel_id_;
            SceneID hov_id_;
            bool depth_only{false};
            bool use_f_id{false};
        };

        struct HalfedgeOpts
        {
            HalfedgeOpts(std::tuple<geometry::Mesh &, gl::Instance &> const &s) : shapes_{s} {}
            std::tuple<geometry::Mesh &, gl::Instance &> shapes_;
            SceneID hov_id_;
            SceneID sel_id_;
        };

        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;

        Renderer(Renderer &&) = delete;
        Renderer &operator=(Renderer &&) = delete;

        static Renderer &Get();
        void Mesh(geometry::Mesh &mesh, MeshOpts const &opts);
        void Halfedge(HalfedgeOpts const &opts);
        void Lines(gl::Lines &mesh, const glm::mat4x4 &view);
        static void Setup(const std::shared_ptr<Opengl> &gl,
                          std::shared_ptr<Camera> const &camera);

        void Clear();
        void ClearDepth();
        void Begin();
        void Complete();
        glm::vec3 GetCameraPos();
        void Outline(scene::Item &item);
        SceneID ReadID(glm::vec2 const &pos);
        static void Destroy();

    private:
        Renderer();

        static inline scene::Renderer *instance_;

        std::shared_ptr<Opengl> gl_;
        std::shared_ptr<Camera> camera_;

        Shader mesh_shader_, lines_shader_, outline_shader_, instanced_shader_;
        Framebuffer framebuffer_, id_resolve_;

        Effects effects_;
    };
}