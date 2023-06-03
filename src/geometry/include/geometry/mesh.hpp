#pragma once

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glad.hpp"
#include "common/widgets_ids.hpp"

#include <vector>

namespace opengl
{
    class Instance;
}

namespace utils
{
    struct Data;
}

namespace geometry
{
    class Mesh
    {
    public:
        using Index = GLuint;
        struct Vert
        {
            glm::vec3 pos;
            glm::vec3 norm;
            GLuint id;
        };
        Mesh();
        Mesh(Mesh &&);
        Mesh(utils::Data const &data);
        /**
         * @brief Construct a new Mesh object
         *
         * @param vertices Vertices vector
         * @param indices  Indexes vector
         */
        Mesh(std::vector<Vert> &&vertices, std::vector<Index> &&indices);
        /**
         * @brief Вызывает openGL draw функцию
         *
         */

        Mesh &operator=(Mesh &&src);
        Mesh &operator=(const Mesh &src) = delete;
        void Destroy();
        void Render();
        void Recreate(utils::Data &&data);

        std::vector<Vert> &Vertices();
        std::vector<Index> &Indices();
        utils::Data GetData();
        size_t IndicesSize();
        GLuint GetVAO();
        void Update();
        bool dirty{true};

    private:
        /**
         * @brief Set the up opengl vao
         *
         */
        void SetupVao();

        GLuint vao_, vbo_, veo_;
        std::vector<Vert> vertices_;
        std::vector<GLuint> indices_;
    };
}