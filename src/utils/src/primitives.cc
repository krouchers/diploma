#include "utils/primitives.hpp"
#include "utils/generate_primitives.hpp"

namespace utils
{
    gl::Mesh CubeMesh(float R)
    {
        auto [verts, indices]{generate::Cube(R)};
        return {std::move(verts), std::move(indices)};
    }
}