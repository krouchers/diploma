#include "scene/scene.hpp"

#include <optional>

void Scene::ForItems(std::function<void(scene::Item &)> f)
{
    for (auto &item : objs_)
    {
        f(item.second);
    }
}

void Scene::Add(scene::Item &&item)
{
    objs_.emplace(nextSceneID++, std::move(item));
}

MayBeItem Scene::Get(SceneID id)
{
    auto entry = objs_.find(id);
    if (entry == objs_.end())
        return std::nullopt;
    return entry->second;
}