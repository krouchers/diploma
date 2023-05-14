#pragma once
#include "glm/mat4x4.hpp"

#include "geometry/mesh.hpp"

#include <vector>

namespace gl
{
    class Instance
    {
    public:
        Instance(utils::Data &&data);
        void Add(glm::mat4x4 &transform, unsigned int id);

    private:
        struct Info
        {
            glm::mat4x4 transform_;
            unsigned int id;
        };

        geometry::Mesh mesh_;
        std::vector<Info> data_;
    };
}