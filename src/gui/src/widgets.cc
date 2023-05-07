#include "gui/widgets.hpp"
#include "glm/gtx/transform.hpp"

#include "scene/pose.hpp"
#include "scene/renderer.hpp"

#include "utils/generate_primitives.hpp"

#include "common/widgets_ids.hpp"
#include "common/colors.hpp"

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

    void Widgets::Render(const glm::vec3 &pos, float scale)
    {
        auto &r = scene::Renderer::Get();
        r.ClearDepth();
        glm::vec3 scl{scale};

        x_move.pose_.pos_ = pos;
        x_move.pose_.scale_ = scl;
        x_move.Render();
        x_move.color_ = Color::red;

        y_move.pose_.pos_ = pos;
        y_move.pose_.scale_ = scl;
        y_move.Render();
        y_move.color_ = Color::green;

        z_move.pose_.pos_ = pos;
        z_move.pose_.scale_ = scl;
        z_move.Render();
        z_move.color_ = Color::blue;
    }
}