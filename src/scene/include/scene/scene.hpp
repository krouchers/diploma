#pragma once

#include "definitions.hpp"
#include "scene/item.hpp"
#include "common/widgets_ids.hpp"
#include "geometry/halfedge_mesh.hpp"

#include <functional>
#include <map>
#include <optional>

using MayBeItem = std::optional<std::reference_wrapper<scene::Item>>;
class GEODIP_API Scene
{
public:
    Scene(){};
    void ForItems(std::function<void(scene::Item &)> f);
    void Add(geometry::HalfedgeMesh &&item);
    MayBeItem Get(SceneID id);
    void Clear();

    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

private:
    std::map<SceneID, scene::Item> objs_;
    SceneID nextSceneID{(SceneID)gui::WidgetsIds::count};
};