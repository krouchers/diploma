#pragma once

#include "geometry/mesh.hpp"
#include "utils/generate_primitives.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <list>
#include <map>
#include <stdexcept>

namespace geometry
{
    struct HalfedgeMesh
    {
        struct Vertex;
        struct Edge;
        struct Face;
        struct Halfedge;

        using VertexRef = std::list<Vertex>::iterator;
        using EdgeRef = std::list<Edge>::iterator;
        using FaceRef = std::list<Face>::iterator;
        using HalfedgeRef = std::list<Halfedge>::iterator;

        using Index = size_t;
        using Size = size_t;

        struct Vertex
        {
            HalfedgeRef halfedge_;
            glm::vec3 pos_;
            Index index;
        };

        struct Edge
        {
            HalfedgeRef halfedge_;
        };

        struct Face
        {
            bool isBoundary_;
            HalfedgeRef halfedge_;
        };

        struct Halfedge
        {
            VertexRef vertex_;
            FaceRef face_;
            EdgeRef edge_;
            HalfedgeRef next_, twin_;
            using IndexPair = std::pair<Index, Index>;
            IndexPair pair;
        };

        HalfedgeMesh() = default;
        HalfedgeMesh(utils::Data &&data);

        gl::Mesh ToMesh();

        void CreateFromData(utils::Data &&data);

        bool CreateFromMesh(gl::Mesh &&mesh)
        {
            CreateFromData({mesh.Vertices(),
                            mesh.Indices()});
            return validate();
        }

        bool validate()
        {
            for (auto vertex : vertices_)
            {
                auto pos{vertex.pos_};
                if (!(std::isfinite(pos.x) && std::isfinite(pos.y) && std::isfinite(pos.z)))
                    return false;
            }
            return true;
        }

        VertexRef NewVertex()
        {
            return vertices_.insert(vertices_.end(), Vertex());
        }
        FaceRef NewFace(bool isBoundary = false)
        {
            return faces_.insert(faces_.end(), Face{isBoundary, halfedges_.end()});
        }
        HalfedgeRef NewHalfedge()
        {
            return halfedges_.insert(halfedges_.end(), Halfedge());
        }

        EdgeRef NewEdge()
        {
            return edges_.insert(edges_.end(), Edge());
        }

        std::list<Vertex> vertices_;
        std::list<Edge> edges_;
        std::list<Face> faces_;
        std::list<Halfedge> halfedges_;
    };
}