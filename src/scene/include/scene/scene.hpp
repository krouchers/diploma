#pragma once

#include "definitions.hpp"
#include "scene/item.hpp"
#include <functional>
#include <map>
#include <optional>

using MayBeItem = std::optional<std::reference_wrapper<scene::Item>>;
class GEODIP_API Scene
{
public:
    Scene(){};
    void ForItems(std::function<void(scene::Item &)> f);
    void Add(scene::Item &&item);
    MayBeItem Get(SceneID id);

    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

private:
    std::map<SceneID, scene::Item> objs_;
    SceneID nextSceneID{1};
};