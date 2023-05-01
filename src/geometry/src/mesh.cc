#include "geometry/mesh.hpp"
#include "utils/generate_primitives.hpp"
namespace gl
{
    Mesh::Mesh()
    {
        SetupVao();
    }

    Mesh::Mesh(Mesh &&src)
        : vertices_{std::move(src.vertices_)},
          indices_{std::move(src.indices_)}
    {
        vao_ = src.vao_;
        src.vao_ = 0;

        vbo_ = src.vbo_;
        src.vbo_ = 0;

        veo_ = src.veo_;
        src.veo_ = 0;

        dirty = src.dirty;
    }

    Mesh::Mesh(std::vector<Vert> &&vertices, std::vector<GLuint> &&indices) : vertices_{vertices}, indices_{indices}
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

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), reinterpret_cast<void *>(0));
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo_);
        glBindVertexArray(0);
    }

    void Mesh::Update()
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_[0]) * vertices_.size(), vertices_.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_[0]) * indices_.size(), indices_.data(), GL_STATIC_DRAW);

        dirty = false;
    }

    void Mesh::Render()
    {
        if (dirty)
            Update();
        glBindVertexArray(vao_);
        glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    std::vector<Mesh::Vert> Mesh::Vertices()
    {
        return vertices_;
    }

    std::vector<Mesh::Index> Mesh::Indices()
    {
        return indices_;
    }

    Mesh::Mesh(utils::Data const &data)
        : vertices_{std::move(data.vertices_)}, indices_{std::move(data.indices_)}
    {
        SetupVao();
    }

    void Mesh::Destroy()
    {
        glDeleteBuffers(1, &vbo_);
        glDeleteBuffers(1, &veo_);
        glDeleteVertexArrays(1, &vao_);
        vao_ = veo_ = vbo_ = 0;
    }

    Mesh &Mesh::operator=(Mesh &&src)
    {
        Destroy();

        vbo_ = src.vbo_;
        veo_ = src.veo_;
        vao_ = src.vao_;

        src.vbo_ = 0;
        src.vao_ = 0;
        src.veo_ = 0;

        dirty = src.dirty;

        vertices_ = std::move(src.vertices_);
        indices_ = std::move(src.indices_);

        return *this;
    }
}