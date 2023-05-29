#pragma once

#include "gui/widgets.hpp"
#include "scene/scene.hpp"

namespace gui
{
    struct Layout
    {
        void Select(SceneID id, Widgets &widgets, glm::vec3 click_dir,
                    glm::vec3 cam_pos, Scene &scene);
        void Render(MayBeItem obj_opt, Widgets &widgets);
        SceneID GetSelectedSceneID();
        glm::vec3 GetSelectedPos(Scene &scene);
        void ApplyTransform(scene::Item &obj, Widgets &widgets);
        void ClearSelection()
        {
            selected_object_ = (SceneID)WidgetsIds::none;
        }

        scene::Pose old_pose_;
        SceneID selected_object_ = (SceneID)WidgetsIds::none;
    };
}