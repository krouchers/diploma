#pragma once
#include "glm/mat4x4.hpp"

#include "geometry/mesh.hpp"

#include "glad.hpp"
#include <vector>

namespace gl
{
    class Instance
    {
    public:
        Instance(geometry::Mesh &&mesh);
        size_t Add(glm::mat4x4 const &transform, unsigned int id);
        void Clear();
        void Render();

        struct Info
        {
            glm::mat4x4 transform_;
            unsigned int id_;
        };

        Info &Get(size_t instance_id);

    private:
        void Update();

        geometry::Mesh mesh_;
        std::vector<Info> data_;
        bool dirty{true};

        GLuint vbo_;
    };
}