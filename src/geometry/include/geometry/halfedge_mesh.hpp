#pragma once

#include "geometry/mesh.hpp"
#include <list>
#include <map>

namespace geometry
{
    class HalfedgeMesh
    {
        struct Vertex;
        struct Edge;
        struct Face;
        struct Halfedge;

        using VertexRef = std::list<Vertex>::iterator;
        using EdgeRef = std::list<Edge>::iterator;
        using FaceRef = std::list<Face>::iterator;
        using HalfedgeRef = std::list<Halfedge>::iterator;

        using VertexCRef = std::list<Vertex>::const_iterator;
        using EdgeCRef = std::list<Edge>::const_iterator;
        using FaceCRef = std::list<Face>::const_iterator;
        using HalfedgeCRef = std::list<Halfedge>::const_iterator;

        using Index = size_t;
        using Size = size_t;

        struct Vertex
        {
            HalfedgeRef halfedge_;
        };

        struct Edge
        {
        };

        struct Face
        {
        };

        struct Halfedge
        {
            FaceRef face_;
        };

    public:
        void CreateFromMesh(gl::Mesh &&mesh)
        {
            auto meshIdxs{mesh.Indices()};
            auto meshVerts{mesh.Vertices()};

            using IndexList = std::vector<Index>;
            // using IndexListCRef = std::vector<Index>::const_iterator;
            using PoligonList = std::vector<IndexList>;
            using PoligonListCRef = std::vector<IndexList>::const_iterator;

            PoligonList polygons;

            for (size_t i{0}; i < meshIdxs.size(); i += 3)
            {
                polygons.push_back({meshIdxs[i], meshIdxs[i + 1], meshIdxs[i + 2]});
            }

            std::map<Index, VertexRef> indToVer;
            for (auto &poligon : polygons)
            {
                if (poligon.size() < 3)
                    throw std::logic_error("Poligon's size must be at least 3");

                for (auto ind : poligon)
                {
                    if (indToVer.find(ind) == indToVer.end())
                    {
                        VertexRef v = NewVertex();
                        v->halfedge_ = halfeges_.end(); // Вершина пока не указывает на халф
                        indToVer[ind] = v;
                    }
                }
            }

            Size numberOfFaces = polygons.size();
            for (Size i{0}; i < numberOfFaces; ++i)
                NewFace();

            using IndexPair = std::pair<Index, Index>;

            std::map<IndexPair, HalfedgeRef> pairToHalfedge;

            PoligonListCRef p;
            FaceRef f;
            for (p = polygons.begin(), f = faces_.begin(); p != polygons.end(); ++p, ++f)
            {
                std::vector<Halfedge> faceHalfedges;

                Size degree = p->size();

                for (Index i{0}; i < degree; ++i)
                {
                    Index a{(*p)[i]};
                    Index b{(*p)[(i + 1) % degree]};
                    IndexPair ab(a, b);
                    HalfedgeRef hab;

                    hab = NewHalfedge();
                    pairToHalfedge[ab] = hab;
                    hab->face_ = f;
                }
            }
        }

    private:
        VertexRef NewVertex()
        {
            return vertices_.insert(vertices_.end(), Vertex());
        }
        FaceRef NewFace()
        {
            return faces_.insert(faces_.end(), Face());
        }
        HalfedgeRef NewHalfedge()
        {
            return halfeges_.insert(halfeges_.end(), Halfedge());
        }

        std::list<Vertex> vertices_;
        std::list<Edge> edges_;
        std::list<Face> faces_;
        std::list<Halfedge> halfeges_;
    };
}