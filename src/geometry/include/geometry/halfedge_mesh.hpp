#pragma once

#include "geometry/mesh.hpp"
#include <list>
#include <map>

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
                        v->halfedge_ = halfedges_.end(); // Вершина пока не указывает на халф
                        indToVer[ind] = v;

                        v->index = ind; // debug
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
                std::vector<HalfedgeRef> faceHalfedges;

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
                    hab->face_->halfedge_ = hab;
                    hab->pair = ab; // debug

                    hab->vertex_ = indToVer[a];
                    hab->vertex_->halfedge_ = hab;

                    IndexPair twin(b, a);
                    auto iba = pairToHalfedge.find(twin);
                    if (iba != pairToHalfedge.end())
                    {
                        auto hba = iba->second;
                        hba->twin_ = hab;
                        hab->twin_ = hba;

                        EdgeRef e = NewEdge();
                        hba->edge_ = e;
                        hab->edge_ = e;
                        e->halfedge_ = hab;
                    }
                    else
                        hab->twin_ = halfedges_.end();

                    faceHalfedges.push_back(hab);
                }

                for (Index i{0}; i < degree; ++i)
                {
                    Index j{(i + 1) % degree};
                    faceHalfedges[i]->next_ = faceHalfedges[j];
                }
            }

            for (VertexRef v = vertices_.begin(); v != vertices_.end(); ++v)
            {
                HalfedgeRef h = v->halfedge_;
                do
                {
                    if (h->twin_ == halfedges_.end())
                    {
                        v->halfedge_ = h;
                        break;
                    }

                    h = h->twin_->next_;
                } while (h != v->halfedge_);
            }

            for (HalfedgeRef h = halfedges_.begin(); h != halfedges_.end(); ++h)
            {
                if (h->twin_ == halfedges_.end())
                {
                    FaceRef b = NewFace(true);
                    std::vector<HalfedgeRef> boundaryLoop;

                    HalfedgeRef i = h;
                    do
                    {
                        HalfedgeRef t = NewHalfedge();
                        boundaryLoop.push_back(t);

                        i->twin_ = t;
                        t->twin_ = i;

                        t->face_ = b;
                        t->vertex_ = i->next_->vertex_;

                        EdgeRef e = NewEdge();
                        i->edge_ = e;
                        t->edge_ = e;
                        e->halfedge_ = i;

                        i = i->next_;
                        while (i->twin_ != halfedges_.end() && i != h)
                        {
                            i = i->twin_->next_;
                        }

                    } while (i != h);

                    b->halfedge_ = boundaryLoop.front();

                    Size degree = boundaryLoop.size();
                    for (Size id{0}; id < degree; ++id)
                        boundaryLoop[id]->next_ = boundaryLoop[(degree - 1 + id) % degree];
                }
            }
            for (auto v = indToVer.begin(); v != indToVer.end(); ++v)
            {
                v->second->pos_ = meshVerts[v->first].pos;
            }
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