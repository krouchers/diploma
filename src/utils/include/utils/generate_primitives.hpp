#pragma once
#include <vector>
#include <geometry/mesh.hpp>

namespace utils
{
    struct Data
    {
        std::vector<geometry::Mesh::Vert> vertices_;
        std::vector<geometry::Mesh::Index> indices_;
    };

    Data GenerateCube(float edgeLenght);
    Data GenerateCone(float bradius, float tradius, float height, int sides = 24, bool caps = 24);
    Data GenerateTorus(float iradius, float oradius);
    Data GenerateSphere(float radius, int level);
    Data GenereateScaleMesh(int size = 1);
    Data GenerateArrow(int size = 1);

    Data merge(Data &&l, Data &&r);
}