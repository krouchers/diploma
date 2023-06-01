#pragma once
#include <string>

#include "geometry/mesh.hpp"

struct Problem
{
    size_t id;
    std::string problem_name_;
    std::string problem_text_;
    geometry::Mesh obj;
};