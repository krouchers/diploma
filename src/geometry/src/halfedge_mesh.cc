#include "geometry/halfedge_mesh.hpp"
#include "common/overloaded.hpp"

#include <unordered_map>
#include <iostream>

namespace std
{
    template <>
    struct hash<glm::vec3>
    {
        size_t operator()(glm::vec3 const &pos) const
        {
            return hash<float>{}(pos.x) ^
                   hash<float>{}(pos.y) ^
                   hash<float>{}(pos.z);
        }
    };
}

namespace geometry
{

    geometry::Mesh HalfedgeMesh::ToMesh()
    {
        std::vector<geometry::Mesh::Vert> mesh_verts;
        std::vector<geometry::Mesh::Index> mesh_indexes;

        std::unordered_map<glm::vec3, geometry::Mesh::Index> posToInd;
        for (auto f = faces_.begin(); f != faces_.end(); ++f)
        {
            if (f->isBoundary_)
                continue;
            HalfedgeRef h = f->halfedge_;
            HalfedgeRef i = h;

            std::vector<glm::vec3> verts;
            do
            {
                verts.push_back(i->vertex_->pos_);
                i = i->next_;
            } while (i != h);

            auto p0 = verts[0];
            auto p1 = verts[1];
            auto p2 = verts[2];
            auto n = glm::normalize(glm::cross(p2 - p0, p1 - p0));

            if (!std::isfinite(n.x))
            {
                n = {};
            }

            mesh_verts.push_back({p0, n, f->id_});
            mesh_verts.push_back({p1, n, f->id_});
            mesh_verts.push_back({p2, n, f->id_});

            geometry::Mesh::Index ind = mesh_indexes.size();

            mesh_indexes.push_back(ind);
            mesh_indexes.push_back(ind + 1);
            mesh_indexes.push_back(ind + 2);
        }

        return geometry::Mesh(std::move(mesh_verts), std::move(mesh_indexes));
    }

    void HalfedgeMesh::CreateFromData(utils::Data &&data)
    {
        auto meshIdxs{data.indices_};
        auto meshVerts{data.vertices_};

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
                    t->pair = {i->pair.second, i->pair.first};

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

    HalfedgeMesh::HalfedgeMesh(utils::Data &&data)
        : HalfedgeMesh()
    {
        CreateFromData(std::move(data));
    }

    HalfedgeMesh::HalfedgeMesh()
        : next_id_{(SceneID)gui::WidgetsIds::count}
    {
    }

    HalfedgeMesh::FaceRef HalfedgeMesh::FacesBegin()
    {
        return faces_.begin();
    }

    HalfedgeMesh::FaceRef HalfedgeMesh::FacesEnd()
    {
        return faces_.end();
    }

    HalfedgeMesh::EdgeRef HalfedgeMesh::EdgesBegin()
    {
        return edges_.begin();
    }

    HalfedgeMesh::EdgeRef HalfedgeMesh::EdgesEnd()
    {
        return edges_.end();
    }

    HalfedgeMesh::VertexRef HalfedgeMesh::VerticesBegin()
    {
        return vertices_.begin();
    }

    HalfedgeMesh::VertexRef HalfedgeMesh::VerticesEnd()
    {
        return vertices_.end();
    }

    glm::vec3 HalfedgeMesh::CenterOf(HalfedgeMesh::ElementRef elem)
    {
        glm::vec3 pos;
        std::variant<int, double> var;
        std::visit(overloaded{
                       [&](VertexRef v)
                       { pos = v->Center(); },
                       [&](EdgeRef)
                       { std::cout << "double\n"; },
                       [&](FaceRef)
                       { std::cout << "double\n"; },
                       [&](HalfedgeRef)
                       { std::cout << "double\n"; },
                   },
                   elem);
        return pos;
    }

    glm::vec3 HalfedgeMesh::Vertex::Center()
    {
        return pos_;
    }

    void HalfedgeMesh::Clear()
    {
        vertices_.clear();
        edges_.clear();
        faces_.clear();
        halfedges_.clear();
    }

    void HalfedgeMesh::CopyTo(HalfedgeMesh &mesh) const
    {
        mesh.Clear();

        std::unordered_map<SceneID, VertexRef> v_map;
        std::unordered_map<SceneID, EdgeRef> e_map;
        std::unordered_map<SceneID, FaceRef> f_map;
        std::unordered_map<SceneID, HalfedgeRef> h_map;

        for (auto v : this->vertices_)
            v_map[v.id_] = mesh.vertices_.insert(mesh.vertices_.end(), v);
        for (auto e : this->edges_)
            e_map[e.id_] = mesh.edges_.insert(mesh.edges_.end(), e);
        for (auto f : this->faces_)
            f_map[f.id_] = mesh.faces_.insert(mesh.faces_.end(), f);
        for (auto h : this->halfedges_)
            h_map[h.id_] = mesh.halfedges_.insert(mesh.halfedges_.end(), h);

        for (auto v : mesh.vertices_)
            v.halfedge_ = h_map[v.halfedge_->id_];

        for (auto e : mesh.edges_)
            e.halfedge_ = h_map[e.halfedge_->id_];

        for (auto f : mesh.faces_)
            f.halfedge_ = h_map[f.halfedge_->id_];

        for (auto h : mesh.halfedges_)
        {
            h.vertex_ = v_map[h.id_];
            h.edge_ = e_map[h.id_];
            h.face_ = f_map[h.id_];
            h.twin_ = h_map[h.twin_->id_];
            h.next_ = h_map[h.next_->id_];
        }
    }
}