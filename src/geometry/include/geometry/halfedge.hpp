#pragma once
#include "halfedge_mesh.hpp"

namespace geometry
{
    class Halfedge
    {
    public:
        FaceRef Face()
        {
            return face_;
        }

    private:
        FaceRef face_;
    };
}