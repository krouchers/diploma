#include "scene/scene.hpp"

#include <optional>

void Scene::ForItems(std::function<void(scene::Item &)> f)
{
    for (auto &item : objs_)
    {
        f(item.second);
    }
}

void Scene::Add(geometry::HalfedgeMesh &&mesh)
{
    auto id = nextSceneID++;
    objs_.emplace(id, scene::Item{id, std::move(mesh)});
}

MayBeItem Scene::Get(SceneID id)
{
    auto entry = objs_.find(id);
    if (entry == objs_.end())
        return std::nullopt;
    return entry->second;
}