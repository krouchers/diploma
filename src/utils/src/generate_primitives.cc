#include "utils/generate_primitives.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <numbers>
#include <map>

namespace utils
{
    Data merge(Data &&l, Data &&r)
    {
        for (auto &i : r.indices_)
            i += l.vertices_.size();
        l.vertices_.insert(l.vertices_.end(), r.vertices_.begin(), r.vertices_.end());
        l.indices_.insert(l.indices_.end(), r.indices_.begin(), r.indices_.end());
        return l;
    }

    Data GenerateCube(float edgeLenght)
    {
        float r{edgeLenght};
        return {{{glm::vec3{-r, -r, -r}, glm::normalize(glm::vec3{-r, -r, -r}), 0},
                 {glm::vec3{r, -r, -r}, glm::normalize(glm::vec3{r, -r, -r}), 0},
                 {glm::vec3{r, r, -r}, glm::normalize(glm::vec3{r, r, -r}), 0},
                 {glm::vec3{-r, r, -r}, glm::normalize(glm::vec3{-r, r, -r}), 0},
                 {glm::vec3{-r, -r, r}, glm::normalize(glm::vec3{-r, -r, r}), 0},
                 {glm::vec3{r, -r, r}, glm::normalize(glm::vec3{r, -r, r}), 0},
                 {glm::vec3{r, r, r}, glm::normalize(glm::vec3{r, r, r}), 0},
                 {glm::vec3{-r, r, r}, glm::normalize(glm::vec3{-r, r, r}), 0}},
                {0, 1, 3, 3, 1, 2, 1, 5, 2, 2, 5, 6, 5, 4, 6, 6, 4, 7,
                 4, 0, 7, 7, 0, 3, 3, 2, 7, 7, 2, 6, 4, 5, 0, 0, 5, 1}};
    }

    Data GenerateCone(float bradius, float tradius, float height, int sides, bool caps)
    {

        const size_t n_sides = sides, n_cap = n_sides + 1;
        const float _2pi = std::numbers::pi * 2.0f;

        std::vector<glm::vec3> vertices(n_cap + n_cap + n_sides * 2 + 2);
        size_t vert = 0;

        vertices[vert++] = glm::vec3(0.0f, 0.0f, 0.0f);
        while (vert <= n_sides)
        {
            float rad = (float)vert / n_sides * _2pi;
            vertices[vert] = glm::vec3(std::cos(rad) * bradius, 0.0f, std::sin(rad) * bradius);
            vert++;
        }
        vertices[vert++] = glm::vec3(0.0f, height, 0.0f);
        while (vert <= n_sides * 2 + 1)
        {
            float rad = (float)(vert - n_sides - 1) / n_sides * _2pi;
            vertices[vert] = glm::vec3(std::cos(rad) * tradius, height, std::sin(rad) * tradius);
            vert++;
        }
        size_t v = 0;
        while (vert <= vertices.size() - 4)
        {
            float rad = (float)v / n_sides * _2pi;
            vertices[vert] = glm::vec3(std::cos(rad) * tradius, height, std::sin(rad) * tradius);
            vertices[vert + 1] = glm::vec3(std::cos(rad) * bradius, 0.0f, std::sin(rad) * bradius);
            vert += 2;
            v++;
        }
        vertices[vert] = vertices[n_sides * 2 + 2];
        vertices[vert + 1] = vertices[n_sides * 2 + 3];

        std::vector<glm::vec3> normals(vertices.size());
        vert = 0;
        while (vert <= n_sides)
        {
            normals[vert++] = glm::vec3(0.0f, -1.0f, 0.0f);
        }
        while (vert <= n_sides * 2 + 1)
        {
            normals[vert++] = glm::vec3(0.0f, 1.0f, 0.0f);
        }

        v = 0;
        while (vert <= vertices.size() - 4)
        {
            float rad = (float)v / n_sides * _2pi;
            float cos = std::cos(rad);
            float sin = std::sin(rad);
            normals[vert] = glm::vec3(cos, 0.0f, sin);
            normals[vert + 1] = normals[vert];
            vert += 2;
            v++;
        }
        normals[vert] = normals[n_sides * 2 + 2];
        normals[vert + 1] = normals[n_sides * 2 + 3];

        size_t n_tris = n_sides + n_sides + n_sides * 2;
        std::vector<geometry::Mesh::Index> triangles(n_tris * 3 + 3);

        geometry::Mesh::Index tri = 0;
        size_t i = 0;
        while (tri < n_sides - 1)
        {
            if (caps)
            {
                triangles[i] = 0;
                triangles[i + 1] = tri + 1;
                triangles[i + 2] = tri + 2;
            }
            tri++;
            i += 3;
        }
        if (caps)
        {
            triangles[i] = 0;
            triangles[i + 1] = tri + 1;
            triangles[i + 2] = 1;
        }
        tri++;
        i += 3;

        while (tri < n_sides * 2)
        {
            if (caps)
            {
                triangles[i] = tri + 2;
                triangles[i + 1] = tri + 1;
                triangles[i + 2] = (GLuint)n_cap;
            }
            tri++;
            i += 3;
        }
        if (caps)
        {
            triangles[i] = (GLuint)n_cap + 1;
            triangles[i + 1] = tri + 1;
            triangles[i + 2] = (GLuint)n_cap;
        }
        tri++;
        i += 3;
        tri++;

        while (tri <= n_tris)
        {
            triangles[i] = tri + 2;
            triangles[i + 1] = tri + 1;
            triangles[i + 2] = tri + 0;
            tri++;
            i += 3;
            triangles[i] = tri + 1;
            triangles[i + 1] = tri + 2;
            triangles[i + 2] = tri + 0;
            tri++;
            i += 3;
        }

        std::vector<geometry::Mesh::Vert> verts;
        for (size_t j = 0; j < vertices.size(); j++)
        {
            verts.push_back({vertices[j], normals[j], 0});
        }
        return {verts, triangles};
    }
    Data GenerateArrow()
    {
        float baseRad = 0.1f;
        float arrowLength = 1.0f;
        float basePart = 0.65;
        float tipPart = 1 - 0.65;
        auto base = GenerateCone(baseRad, baseRad, arrowLength * basePart, 10, true);
        auto tip = GenerateCone(baseRad * 1.75, 0.01f, arrowLength * tipPart, 10, true);
        for (auto &v : tip.vertices_)
            v.pos.y += arrowLength * basePart;
        return merge(std::move(base), std::move(tip));
    }

    Data GenerateTorus(float iradius, float oradius)
    {
        const int n_rad_sides = 48, n_sides = 24;
        const float _2pi = std::numbers::pi * 2.0f;
        iradius = oradius - iradius;

        std::vector<glm::vec3> vertices((n_rad_sides + 1) * (n_sides + 1));
        for (int seg = 0; seg <= n_rad_sides; seg++)
        {

            int cur_seg = seg == n_rad_sides ? 0 : seg;

            float t1 = (float)cur_seg / n_rad_sides * _2pi;
            glm::vec3 r1(std::cos(t1) * oradius, 0.0f, std::sin(t1) * oradius);

            for (int side = 0; side <= n_sides; side++)
            {

                int cur_side = side == n_sides ? 0 : side;
                float t2 = (float)cur_side / n_sides * _2pi;
                glm::vec3 r2 = glm::rotate(glm::mat4x4(1.0f), glm::degrees(-t1), glm::vec3{0.0f, 1.0f, 0.0f}) *
                               glm::vec4(std::sin(t2) * iradius, std::cos(t2) * iradius, 0.0f, 0.0f);

                vertices[side + seg * (n_sides + 1)] = r1 + r2;
            }
        }

        std::vector<glm::vec3> normals(vertices.size());
        for (int seg = 0; seg <= n_rad_sides; seg++)
        {

            int cur_seg = seg == n_rad_sides ? 0 : seg;
            float t1 = (float)cur_seg / n_rad_sides * _2pi;
            glm::vec3 r1(std::cos(t1) * oradius, 0.0f, std::sin(t1) * oradius);

            for (int side = 0; side <= n_sides; side++)
            {
                normals[side + seg * (n_sides + 1)] =
                    glm::normalize(vertices[side + seg * (n_sides + 1)] - r1);
            }
        }

        int n_faces = (int)vertices.size();
        int n_tris = n_faces * 2;
        int n_idx = n_tris * 3;
        std::vector<geometry::Mesh::Index> triangles(n_idx);

        size_t i = 0;
        for (int seg = 0; seg <= n_rad_sides; seg++)
        {
            for (int side = 0; side <= n_sides - 1; side++)
            {

                int current = side + seg * (n_sides + 1);
                int next = side + (seg < (n_rad_sides) ? (seg + 1) * (n_sides + 1) : 0);

                if (i < triangles.size() - 6)
                {
                    triangles[i++] = current;
                    triangles[i++] = next;
                    triangles[i++] = next + 1;
                    triangles[i++] = current;
                    triangles[i++] = next + 1;
                    triangles[i++] = current + 1;
                }
            }
        }

        std::vector<geometry::Mesh::Vert> verts;
        for (size_t j = 0; j < vertices.size(); j++)
        {
            verts.push_back({vertices[j], normals[j], 0});
        }
        return {verts, triangles};
    }

    Data GenereateScaleMesh()
    {
        auto cube = GenerateCube(0.1f);
        auto cone = GenerateCone(0.05f, 0.05f, 0.8f, 18, true);
        for (auto &v : cube.vertices_)
        {
            v.pos.y += 0.8;
        }
        return merge(std::move(cube), std::move(cone));
    }

    Data GenerateSphere(float radius, int level)
    {
        struct TriIdx
        {
            int v1, v2, v3;
        };

        auto middle_point = [&](int p1, int p2, std::vector<glm::vec3> &vertices,
                                std::map<int64_t, size_t> &cache, float radius) -> size_t
        {
            bool firstIsSmaller = p1 < p2;
            int64_t smallerIndex = firstIsSmaller ? p1 : p2;
            int64_t greaterIndex = firstIsSmaller ? p2 : p1;
            int64_t key = (smallerIndex << 32ll) + greaterIndex;

            auto entry = cache.find(key);
            if (entry != cache.end())
            {
                return entry->second;
            }

            glm::vec3 point1 = vertices[p1];
            glm::vec3 point2 = vertices[p2];
            glm::vec3 middle((point1.x + point2.x) / 2.0f, (point1.y + point2.y) / 2.0f,
                             (point1.z + point2.z) / 2.0f);
            size_t i = vertices.size();
            vertices.push_back(glm::normalize(middle) * radius);
            cache[key] = i;
            return i;
        };

        std::vector<glm::vec3> vertices;
        std::map<int64_t, size_t> middlePointIndexCache;
        float t = (1.0f + std::sqrt(5.0f)) / 2.0f;
        vertices.push_back(glm::normalize(glm::vec3(-1.0f, t, 0.0f)) * radius);
        vertices.push_back(glm::normalize(glm::vec3(1.0f, t, 0.0f)) * radius);
        vertices.push_back(glm::normalize(glm::vec3(-1.0f, -t, 0.0f)) * radius);
        vertices.push_back(glm::normalize(glm::vec3(1.0f, -t, 0.0f)) * radius);
        vertices.push_back(glm::normalize(glm::vec3(0.0f, -1.0f, t)) * radius);
        vertices.push_back(glm::normalize(glm::vec3(0.0f, 1.0f, t)) * radius);
        vertices.push_back(glm::normalize(glm::vec3(0.0f, -1.0f, -t)) * radius);
        vertices.push_back(glm::normalize(glm::vec3(0.0f, 1.0f, -t)) * radius);
        vertices.push_back(glm::normalize(glm::vec3(t, 0.0f, -1.0f)) * radius);
        vertices.push_back(glm::normalize(glm::vec3(t, 0.0f, 1.0f)) * radius);
        vertices.push_back(glm::normalize(glm::vec3(-t, 0.0f, -1.0f)) * radius);
        vertices.push_back(glm::normalize(glm::vec3(-t, 0.0f, 1.0f)) * radius);

        std::vector<TriIdx> faces;
        faces.push_back(TriIdx{0, 11, 5});
        faces.push_back(TriIdx{0, 5, 1});
        faces.push_back(TriIdx{0, 1, 7});
        faces.push_back(TriIdx{0, 7, 10});
        faces.push_back(TriIdx{0, 10, 11});
        faces.push_back(TriIdx{1, 5, 9});
        faces.push_back(TriIdx{5, 11, 4});
        faces.push_back(TriIdx{11, 10, 2});
        faces.push_back(TriIdx{10, 7, 6});
        faces.push_back(TriIdx{7, 1, 8});
        faces.push_back(TriIdx{3, 9, 4});
        faces.push_back(TriIdx{3, 4, 2});
        faces.push_back(TriIdx{3, 2, 6});
        faces.push_back(TriIdx{3, 6, 8});
        faces.push_back(TriIdx{3, 8, 9});
        faces.push_back(TriIdx{4, 9, 5});
        faces.push_back(TriIdx{2, 4, 11});
        faces.push_back(TriIdx{6, 2, 10});
        faces.push_back(TriIdx{8, 6, 7});
        faces.push_back(TriIdx{9, 8, 1});

        for (int i = 0; i < level; i++)
        {
            std::vector<TriIdx> faces2;
            for (auto tri : faces)
            {
                int a = (int)middle_point(tri.v1, tri.v2, vertices, middlePointIndexCache, radius);
                int b = (int)middle_point(tri.v2, tri.v3, vertices, middlePointIndexCache, radius);
                int c = (int)middle_point(tri.v3, tri.v1, vertices, middlePointIndexCache, radius);
                faces2.push_back(TriIdx{tri.v1, a, c});
                faces2.push_back(TriIdx{tri.v2, b, a});
                faces2.push_back(TriIdx{tri.v3, c, b});
                faces2.push_back(TriIdx{a, b, c});
            }
            faces = faces2;
        }

        std::vector<geometry::Mesh::Index> triangles;
        for (size_t i = 0; i < faces.size(); i++)
        {
            triangles.push_back(faces[i].v1);
            triangles.push_back(faces[i].v2);
            triangles.push_back(faces[i].v3);
        }

        std::vector<glm::vec3> normals(vertices.size());
        for (size_t i = 0; i < normals.size(); i++)
            normals[i] = glm::normalize(vertices[i]);

        std::vector<geometry::Mesh::Vert> verts;
        for (size_t i = 0; i < vertices.size(); i++)
        {
            verts.push_back({vertices[i], normals[i], 0});
        }
        return {verts, triangles};
    }
}