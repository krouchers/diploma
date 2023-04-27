#pragma once
#include <vector>
#include <geometry/mesh.hpp>

namespace utils
{
    struct Data
    {
        std::vector<gl::Mesh::Vert> vertices_;
        std::vector<gl::Mesh::Index> indices_;
    };

    Data GenerateCube(float edgeLenght);
}