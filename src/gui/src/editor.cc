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

    void Editor::Render(MayBeItem obj_opt)
    {
        if (obj_opt)
        {
            scene::Item &item = obj_opt.value();
            auto &r = scene::Renderer::Get();
            auto cam_pos = r.GetCameraPos();
            auto obj_pos = item.pose_.pos_;
            auto length = glm::length(obj_pos - cam_pos);
            r.Outline(item);
            float scale = length / 50.0f;
            widgets_.Render(obj_pos, scale);
        }
    }
}