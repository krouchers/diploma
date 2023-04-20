#pragma once

#include <variant>

#include "item.hpp"
#include "functional"

using Scene_ID = unsigned int;

class Scene
{
public:
    void ForItems(std::function<void(scene::Item &)> f);
    void Add(scene::Item &&item);

private:
    std::vector<scene::Item> objs_;
};