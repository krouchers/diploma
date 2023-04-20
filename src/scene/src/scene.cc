#include "scene/scene.hpp"

void Scene::ForItems(std::function<void(scene::Item &)> f)
{
    for (auto &item : objs_)
    {
        f(item);
    }
}

void Scene::Add(scene::Item &&item)
{
    objs_.push_back(std::move(item));
}
