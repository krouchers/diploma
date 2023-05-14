#include "gui/layout.hpp"
#include "scene/renderer.hpp"
#include "scene/item.hpp"

namespace gui
{
    SceneID Layout::GetSelectedSceneID()
    {
        return selected_object_;
    }

    void Layout::Render(MayBeItem obj_opt, Widgets &widgets)
    {
        if (obj_opt)
        {
            scene::Item &item = obj_opt.value();
            auto &r = scene::Renderer::Get();
            auto cam_pos = r.GetCameraPos();
            auto obj_pos = item.pose_.pos_;
            auto length = glm::length(glm::vec3{0.0f, 0.0f, 0.0f} - cam_pos);
            r.Outline(item);
            float scale = length / 5.0f;
            widgets.Render(obj_pos, std::min(scale, 3.0f));
        }
    }

    void Layout::Select(SceneID id)
    {
        if (id >= (SceneID)WidgetsIds::count)
            selected_object_ = id;
    }
}