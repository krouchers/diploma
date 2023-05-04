#include "opengl/lines.hpp"
#include "opengl/opengl.hpp"

namespace gl
{

    void Lines::Add(const glm::vec3 &start, const glm::vec3 &end, const glm::vec3 &color)
    {
        veritces_.push_back({start, color});
        veritces_.push_back({end, color});

        dirty = true;
    }

    Lines::Lines()
    {
        glGenVertexArrays(1, &vao_);
        glGenBuffers(1, &vbo_);

        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), static_cast<void *>(0));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vert), reinterpret_cast<void *>(sizeof(glm::vec3)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void Lines::Update()
    {
        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * veritces_.size(), veritces_.data(), GL_STATIC_DRAW);
        glBindVertexArray(0);
        dirty = false;
    }

    void Lines::Render()
    {
        glLineWidth(1.0f);
        if (dirty)
            Update();
        glBindVertexArray(vao_);
        glDrawArrays(GL_LINES, 0, veritces_.size());
        glBindVertexArray(0);
    }
}