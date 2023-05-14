#pragma once

#include "gui/widgets.hpp"
#include "scene/scene.hpp"

namespace gui
{
    struct Layout 
    {
        void Select(SceneID id);
        void Render(MayBeItem obj_opt, Widgets &widgets);
        SceneID GetSelectedSceneID();
        void ClearSelection()
        {
            selected_object_ = (SceneID)WidgetsIds::none;
        }

        SceneID selected_object_ = (SceneID)WidgetsIds::none;
    };
}