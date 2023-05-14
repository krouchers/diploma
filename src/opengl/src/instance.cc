#include "opengl/instance.hpp"

namespace gl
{
    void Instance::Add(glm::mat4x4 &transform, unsigned int id)
    {
        data_.push_back({transform, id});
    }

    Instance::Instance(utils::Data &&data)
        : mesh_{std::move(data)}
    {
    }
}