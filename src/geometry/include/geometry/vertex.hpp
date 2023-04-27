#pragma once
#include "geometry/halfedge_mesh.hpp"

namespace geometry
{
    class Vertex
    {
        HalfedgeRef halfedge_;
        friend class HalfedgeMesh;
    };
}