#include "gui/editor.hpp"
#include "scene/renderer.hpp"
#include "scene/item.hpp"

namespace gui
{

    void Editor::Select(SceneID id)
    {
        selected_object_ = id;
    }

    SceneID Editor::GetSelectedSceneID()
    {
        return selected_object_;
    }

    void Editor::Render(MayBeItem obj_opt, const glm::mat4x4 &view)
    {
        if (obj_opt)
        {
            scene::Item &item = obj_opt.value();
            auto &r = scene::Renderer::Get();
            r.Outline(item);
            (void)view;
            // widgets_.Render(item.pose_.pos_, view);
        }
    }
}