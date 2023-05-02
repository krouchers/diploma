#pragma once

#include "definitions.hpp"
#include "item.hpp"
#include "functional"

using Scene_ID = unsigned int;

class GEODIP_API Scene
{
public:
    Scene(){};
    void ForItems(std::function<void(scene::Item &)> f);
    void Add(scene::Item &&item);

    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

private:
    std::vector<scene::Item> objs_;
};