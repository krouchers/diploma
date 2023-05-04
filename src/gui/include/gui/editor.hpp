#pragma once

#include "gui/widgets.hpp"
#include "scene/scene.hpp"

namespace gui
{
    class Editor
    {
    public:
        void Select(SceneID id);
        void Render(MayBeItem obj);
        SceneID GetSelectedSceneID();

    private:
        SceneID selected_object_ = (SceneID)WidgetsIds::none;
    };
}