#include "gui/widgets.hpp"
#include "glm/gtx/transform.hpp"

#include "scene/pose.hpp"
#include "scene/renderer.hpp"

#include "utils/generate_primitives.hpp"
#include "utils/log.hpp"

#include "common/widgets_ids.hpp"
#include "common/colors.hpp"

#include "geometry/line.hpp"
#include "geometry/plane.hpp"

#include <cmath>

namespace gui
{
    Widgets::Widgets()
        : x_move{(SceneID)WidgetsIds::x_move,
                 scene::Pose::Rotated({0.0, 0.0f, -90.0f}), utils::GenerateArrow()},
          y_move{(SceneID)WidgetsIds::y_move, {}, utils::GenerateArrow()},
          z_move{(SceneID)WidgetsIds::z_move,
                 scene::Pose::Rotated({90.0f, 0.0f, 0.0f}), utils::GenerateArrow()}
    {
        x_move.color_ = Color::red;
        y_move.color_ = Color::green;
        z_move.color_ = Color::blue;
    }

    void Widgets::Render(const glm::vec3 &pos, float scale)
    {
        auto &r = scene::Renderer::Get();
        r.ClearDepth();
        glm::vec3 scl{scale};

        x_move.pose_.pos_ = pos;
        x_move.pose_.scale_ = scl;
        x_move.Render();

        y_move.pose_.pos_ = pos;
        y_move.pose_.scale_ = scl;
        y_move.Render();

        z_move.pose_.pos_ = pos;
        z_move.pose_.scale_ = scl;
        z_move.Render();
    }

    void Widgets::Select(SceneID id)
    {
        dragging_ = true;
        switch (id)
        {
        case (SceneID)WidgetsIds::x_move:
            active_ = WidgetType::move;
            axis_ = Axis::X;
            break;
        case (SceneID)WidgetsIds::y_move:
            active_ = WidgetType::move;
            axis_ = Axis::Y;
            break;
        case (SceneID)WidgetsIds::z_move:
            active_ = WidgetType::move;
            axis_ = Axis::Z;
            break;

        default:
            dragging_ = false;
            break;
        }
    }

    void Widgets::StartDrag(scene::Pose const &pose,
                            glm::vec3 const &click_dir,
                            glm::vec3 const &camera_pos)
    {
        drag_start_ = drag_end_ = AxisHit(pose, click_dir, camera_pos);
    }

    void Widgets::DragTo(scene::Pose const &pose,
                            glm::vec3 const &click_dir,
                            glm::vec3 const &camera_pos)
    {
        drag_start_ = drag_end_;
        drag_end_ = AxisHit(pose, click_dir, camera_pos);
    }

    void Widgets::EndDrag()
    {
        dragging_  = false;
    }

    scene::Pose Widgets::ApplyAction(scene::Pose const &old_pose)
    {
        scene::Pose new_pose{old_pose};
        switch (active_)
        {
        case WidgetType::move:
            new_pose.pos_ = drag_end_ - drag_start_ + old_pose.pos_;
            break;

        default:
            break;
        }
        return new_pose;
    }
    glm::vec3 Widgets::AxisHit(scene::Pose const &pose, glm::vec3 const &click_dir, glm::vec3 const &camera_pos)
    {
        geometry::Plane f{pose.pos_, {0.0f, 1.0f, 0.0f}};
        geometry::Plane s{pose.pos_, {0.0f, 0.0f, 1.0f}};

        geometry::Line select{camera_pos, click_dir};
        geometry::Line move_axis{pose.pos_, {1.0f, 0.0f, 0.0f}};

        plane_selection_pos_f_ = f.hit(select);
        plane_selection_pos_s_ = s.hit(select);

        if (glm::length(plane_selection_pos_f_ - camera_pos) <=
            glm::length(plane_selection_pos_s_ - camera_pos))
            move_selection_pos_ = move_axis.ClosestTo(plane_selection_pos_f_);
        else
            move_selection_pos_ = move_axis.ClosestTo(plane_selection_pos_s_);

        return move_selection_pos_;
    }
}