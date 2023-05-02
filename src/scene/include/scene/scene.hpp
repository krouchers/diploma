#pragma once

#include "definitions.hpp"
#include "item.hpp"
#include "functional"

#include <map>

using SceneID = unsigned int;

class GEODIP_API Scene
{
public:
    Scene(){};
    void ForItems(std::function<void(SceneID, scene::Item &)> f);
    void Add(scene::Item &&item);

    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

private:
    std::map<SceneID, scene::Item> objs_;
    SceneID nextSceneID{1};
};