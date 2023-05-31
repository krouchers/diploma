#pragma once

#include "geometry/mesh.hpp"
#include "utils/generate_primitives.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <list>
#include <map>
#include <stdexcept>
#include <variant>

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

        using ElementRef = std::variant<
            VertexRef,
            EdgeRef,
            FaceRef,
            HalfedgeRef>;

        using Index = size_t;
        using Size = size_t;

        static glm::vec3 CenterOf(ElementRef elem);

        struct Vertex
        {
            Vertex(SceneID id) : id_{(SceneID)id} {}
            glm::vec3 Center();
            SceneID id_;
            HalfedgeRef halfedge_;
            glm::vec3 pos_;
            Index index;
        };

        struct Edge
        {
            Edge(SceneID id) : id_{(SceneID)id} {}
            SceneID id_;
            HalfedgeRef halfedge_;
        };

        struct Face
        {
            Face(SceneID id, bool is_boundary) : id_{(SceneID)id},
                                                 isBoundary_{is_boundary} {}
            SceneID id_;
            bool isBoundary_;
            HalfedgeRef halfedge_;
        };

        struct Halfedge
        {
            Halfedge(SceneID id) : id_{(SceneID)id} {}
            SceneID id_;
            VertexRef vertex_;
            FaceRef face_;
            EdgeRef edge_;
            HalfedgeRef next_, twin_;
            using IndexPair = std::pair<Index, Index>;
            //For Validation
            IndexPair pair;
        };

        HalfedgeMesh();
        HalfedgeMesh(utils::Data &&data);

        geometry::Mesh ToMesh();

        void CopyTo(HalfedgeMesh &mesh) const;
        void Clear();

        void CreateFromData(utils::Data &&data);

        bool CreateFromMesh(geometry::Mesh &&mesh)
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
            return vertices_.insert(vertices_.end(), Vertex{next_id_++});
        }
        FaceRef NewFace(bool isBoundary = false)
        {
            return faces_.insert(faces_.end(), Face{next_id_++, isBoundary});
        }
        HalfedgeRef NewHalfedge()
        {
            return halfedges_.insert(halfedges_.end(), Halfedge{next_id_++});
        }

        EdgeRef NewEdge()
        {
            return edges_.insert(edges_.end(), Edge{next_id_++});
        }

        FaceRef FacesBegin();
        FaceRef FacesEnd();

        EdgeRef EdgesBegin();
        EdgeRef EdgesEnd();

        VertexRef VerticesBegin();
        VertexRef VerticesEnd();

        SceneID next_id_;

        std::list<Vertex> vertices_;
        std::list<Edge> edges_;
        std::list<Face> faces_;
        std::list<Halfedge> halfedges_;
    };
}