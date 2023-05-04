#pragma once

#include "glm/vec3.hpp"

#include <vector>

namespace gl
{
    class Lines
    {
    public:
        struct Vert
        {
            glm::vec3 Pos;
            glm::vec3 Col;
        };

        Lines();
        void Create();
        void Update();
        void Render();
        void Add(const glm::vec3 &start, const glm::vec3 &end, const glm::vec3 &color);

    private:
        unsigned int vao_, vbo_;
        std::vector<Vert> veritces_;
        bool dirty{true};
    };
}