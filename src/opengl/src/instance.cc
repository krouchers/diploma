#include "opengl/instance.hpp"

namespace gl
{
    void Instance::Add(glm::mat4x4 const &transform, unsigned int id)
    {
        data_.push_back({transform, id});
    }

    Instance::Instance(geometry::Mesh &&mesh)
        : mesh_{std::move(mesh)}
    {
        glGenBuffers(1, &vbo_);
        glBindVertexArray(mesh_.GetVAO());

        glBindBuffer(GL_ARRAY_BUFFER, vbo_);

        glEnableVertexAttribArray(3);
        glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT,
                               sizeof(Info),
                               reinterpret_cast<void *>(offsetof(Info, id_)));
        glVertexAttribDivisor(3, 1);

        int base_ind = 4;
        for (int i = 0; i < 4; ++i)
        {
            glEnableVertexAttribArray(base_ind + i);
            glVertexAttribPointer(base_ind + i, 4, GL_FLOAT,
                                  GL_FALSE, sizeof(Info),
                                  reinterpret_cast<void *>(offsetof(Info, transform_) + i * sizeof(glm::vec4)));
            glVertexAttribDivisor(base_ind + i, 1);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Instance::Update()
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(Info) * data_.size(),
                     data_.data(), GL_DYNAMIC_DRAW);

        dirty = false;
    }

    void Instance::Render()
    {
        if (mesh_.dirty)
            mesh_.Update();
        if (dirty)
            Update();

        glBindVertexArray(mesh_.GetVAO());
        glDrawElementsInstanced(GL_TRIANGLES, mesh_.IndicesSize(), GL_UNSIGNED_INT,
                                nullptr, data_.size());
        glBindVertexArray(0);
    }

    void Instance::Clear()
    {
        data_.clear();
        dirty = true;
    }
}