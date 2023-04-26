#include "geometry/mesh.hpp"
namespace gl
{

    Mesh::Mesh(std::vector<Vert> && vertices, std::vector<GLuint> && indices) : vertices_{vertices}, indices_{indices}
    {
        SetupVao();
    }

    void Mesh::SetupVao()
    {
        glGenVertexArrays(1, &vao_);

        glBindVertexArray(vao_);
        glGenBuffers(1, &vbo_);
        glGenBuffers(1, &veo_);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_[0]) * vertices_.size(), vertices_.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_[0]) * indices_.size(), indices_.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void *>(0));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void *>(sizeof(float) * 3));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void *>(sizeof(float) * 6));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    void Mesh::Render()
    {
        glBindVertexArray(vao_);
        glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
}