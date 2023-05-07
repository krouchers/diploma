#include "gui/widgets.hpp"
#include "glm/gtx/transform.hpp"
#include "scene/pose.hpp"
#include "utils/generate_primitives.hpp"
#include "common/widgets_ids.hpp"

namespace gui
{
    Widgets::Widgets()
        : x_move{(SceneID)WidgetsIds::x_move,
                 scene::Pose::Rotated({0.0, 0.0f, -90.0f}), utils::GenerateArrow()},
          y_move{(SceneID)WidgetsIds::y_move, {}, utils::GenerateArrow()},
          z_move{(SceneID)WidgetsIds::z_move,
                 scene::Pose::Rotated({90.0f, 0.0f, 0.0f}), utils::GenerateArrow()}
    {
    }

    void Widgets::Render(const glm::vec3 &pos, const glm::mat4x4 &view)
    {
        x_move.pose_.pos_ = pos;
        x_move.Render(view);

        y_move.pose_.pos_ = pos;
        y_move.Render(view);

        z_move.pose_.pos_ = pos;
        z_move.Render(view);
    }
}