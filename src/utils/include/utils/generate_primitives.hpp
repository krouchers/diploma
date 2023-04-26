#pragma once
#include <vector>
#include <mesh.hpp>

namespace utils
{
    namespace generate
    {

        struct Data
        {
            std::vector<gl::Mesh::Vert> vertices_;
            std::vector<gl::Mesh::Index> indices_;
        };

        Data Cube(float r);
    }
}