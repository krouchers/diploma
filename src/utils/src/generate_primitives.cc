#include "utils/generate_primitives.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <numbers>

namespace utils
{

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
        // return {{{glm::vec3{-r, -r, -0}, glm::normalize(glm::vec3{-r, -r, -r}), 0},
        //          {glm::vec3{r, -r, -0}, glm::normalize(glm::vec3{-r, -r, -r}), 0},
        //          {glm::vec3{r, r, -0}, glm::normalize(glm::vec3{-r, -r, -r}), 0},
        //          {glm::vec3{-r, r, -0}, glm::normalize(glm::vec3{-r, -r, -r}), 0}},
        //         {0, 1, 2, 2, 3, 0}};
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
        std::vector<gl::Mesh::Index> triangles(n_tris * 3 + 3);

        gl::Mesh::Index tri = 0;
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

        std::vector<gl::Mesh::Vert> verts;
        for (size_t j = 0; j < vertices.size(); j++)
        {
            verts.push_back({vertices[j], normals[j], 0});
        }
        return {verts, triangles};
    }
}