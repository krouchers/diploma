#pragma once

#include "gui/widgets.hpp"
#include "scene/scene.hpp"

namespace gui
{
    struct Layout
    {
        void Select(SceneID id, Scene &scene, Widgets &widgets);
        void Render(MayBeItem obj_opt, Widgets &widgets);
        SceneID GetSelectedSceneID();
        glm::vec3 GetSelectedPos(Scene &scene);
        void ClearSelection()
        {
            selected_object_ = (SceneID)WidgetsIds::none;
        }

        scene::Pose old_pose_;
        SceneID selected_object_ = (SceneID)WidgetsIds::none;
    };
}