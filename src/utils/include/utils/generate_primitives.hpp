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
    Data GenerateCone(float bradius, float tradius, float height, int sides, bool caps);
    Data GenerateTorus(float iradius, float oradius);
    Data GenereateScaleMesh();
    Data GenerateArrow();
}