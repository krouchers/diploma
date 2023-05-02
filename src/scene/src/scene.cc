#include "scene/scene.hpp"

void Scene::ForItems(std::function<void(SceneID, scene::Item &)> f)
{
    for (auto &[id, item] : objs_)
    {
        f(id, item);
    }
}

void Scene::Add(scene::Item &&item)
{
    objs_.emplace(nextSceneID++, std::move(item));
}
