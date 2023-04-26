#pragma once

#include "geometry/edge.hpp"
#include "geometry/face.hpp"
#include "geometry/vertex.hpp"
#include "geometry/halfedge.hpp"

#include "mesh.hpp"

#include <list>

namespace geometry
{
    class HalfedgeMesh
    {
    public:
        using EdgeRef = std::list<Edge>::iterator;
        using FaceRef = std::list<Edge>::iterator;
        using VertexRef = std::list<Edge>::iterator;

        void CreateFromMesh(gl::Mesh &&mesh);

    private:
        std::list<Vertex> vertices_;
        std::list<Edge> edges_;
        std::list<Face> faces_;
        std::list<Halfedge> halfeges_;
    };
}