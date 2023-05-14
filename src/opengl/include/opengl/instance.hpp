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
        void Add(glm::mat4x4 const &transform, unsigned int id);
        void Render();

    private:
        void Update();
        struct Info
        {
            glm::mat4x4 transform_;
            unsigned int id_;
        };

        geometry::Mesh mesh_;
        std::vector<Info> data_;
        bool dirty{true};

        GLuint vbo_;
    };
}