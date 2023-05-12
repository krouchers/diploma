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
#include "math/common.hpp"

#include "imgui.h"

#include <cmath>

namespace gui
{
    Widgets::Widgets()
        : x_move_{(SceneID)WidgetsIds::x_move,
                  scene::Pose::Rotated({0.0, 0.0f, -90.0f}), utils::GenerateArrow()},
          y_move_{(SceneID)WidgetsIds::y_move, {}, utils::GenerateArrow()},
          z_move_{(SceneID)WidgetsIds::z_move,
                  scene::Pose::Rotated({90.0f, 0.0f, 0.0f}), utils::GenerateArrow()},
          x_rot_{(SceneID)WidgetsIds::x_rot, scene::Pose::Rotated({0.0, 0.0f, -90.0f}), utils::GenerateTorus(0.965f, 1.0f)},
          y_rot_{(SceneID)WidgetsIds::y_rot, {}, utils::GenerateTorus(0.965f, 1.0f)},
          z_rot_{(SceneID)WidgetsIds::z_rot, scene::Pose::Rotated({90.0f, 0.0f, 0.0f}), utils::GenerateTorus(0.965f, 1.0f)},
          x_scale_{(SceneID)WidgetsIds::x_scale, scene::Pose::Rotated({0.0, 0.0f, -90.0f}), utils::GenereateScaleMesh()},
          y_scale_{(SceneID)WidgetsIds::y_scale, {}, utils::GenereateScaleMesh()},
          z_scale_{(SceneID)WidgetsIds::z_scale,
                   scene::Pose::Rotated({90.0f, 0.0f, 0.0f}), utils::GenereateScaleMesh()}

    {
        x_scale_.color_ = x_rot_.color_ = x_move_.color_ = Color::red;
        y_scale_.color_ = y_rot_.color_ = y_move_.color_ = Color::green;
        z_scale_.color_ = z_rot_.color_ = z_move_.color_ = Color::blue;
    }

    void Widgets::Render(const glm::vec3 &pos, float scale)
    {
        auto &r = scene::Renderer::Get();
        r.ClearDepth();
        glm::vec3 scl{scale};
        switch (active_)
        {
        case WidgetType::move:
        {
            if (!dragging_)
            {
                x_move_.pose_.scale_ = scl;
                x_move_.pose_.pos_ = pos;
                x_move_.Render();

                y_move_.pose_.scale_ = scl;
                y_move_.pose_.pos_ = pos;
                y_move_.Render();

                z_move_.pose_.scale_ = scl;
                z_move_.pose_.pos_ = pos;
                z_move_.Render();
            }
            break;
        }
        case WidgetType::rotate:
        {
            if (!dragging_ || axis_ == Axis::X)
            {
                x_rot_.pose_.pos_ = pos;
                x_rot_.pose_.scale_ = scl;
                x_rot_.Render();
            }

            if (!dragging_ || axis_ == Axis::Y)
            {
                y_rot_.pose_.pos_ = pos;
                y_rot_.pose_.scale_ = scl;
                y_rot_.Render();
            }

            if (!dragging_ || axis_ == Axis::Z)
            {
                z_rot_.pose_.pos_ = pos;
                z_rot_.pose_.scale_ = scl;
                z_rot_.Render();
                break;
            }
        }
        case WidgetType::scale:
        {
            if (!dragging_)
            {
                x_scale_.pose_.pos_ = pos;
                x_scale_.pose_.scale_ = scl;
                x_scale_.Render();

                y_scale_.pose_.pos_ = pos;
                y_scale_.pose_.scale_ = scl;
                y_scale_.Render();

                z_scale_.pose_.pos_ = pos;
                z_scale_.pose_.scale_ = scl;
                z_scale_.Render();
            }
            break;
        }
        default:
            break;
        }
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

        case (SceneID)WidgetsIds::x_rot:
            active_ = WidgetType::rotate;
            axis_ = Axis::X;
            break;
        case (SceneID)WidgetsIds::y_rot:
            active_ = WidgetType::rotate;
            axis_ = Axis::Y;
            break;
        case (SceneID)WidgetsIds::z_rot:
            active_ = WidgetType::rotate;
            axis_ = Axis::Z;
            break;

        case (SceneID)WidgetsIds::x_scale:
            active_ = WidgetType::scale;
            axis_ = Axis::X;
            break;
        case (SceneID)WidgetsIds::y_scale:
            active_ = WidgetType::scale;
            axis_ = Axis::Y;
            break;
        case (SceneID)WidgetsIds::z_scale:
            active_ = WidgetType::scale;
            axis_ = Axis::Z;
            break;
        default:
            dragging_ = false;
            break;
        }
    }

    void Widgets::StartDrag(glm::vec3 const &pos,
                            glm::vec3 const &click_dir,
                            glm::vec3 const &camera_pos)
    {
        if (active_ == WidgetType::rotate)
        {
            drag_end_ = drag_start_ = glm::normalize(pos - PlaneHit(pos, click_dir, camera_pos));
        }
        else if (active_ == WidgetType::move)
            drag_start_ = drag_end_ = AxisHit(pos, click_dir, camera_pos);
        else
        {
            drag_start_ = AxisHit(pos, click_dir, camera_pos);
            drag_end_ = glm::vec3(1.0f);
        }
    }

    void Widgets::DragTo(glm::vec3 const &pos,
                         glm::vec3 const &click_dir,
                         glm::vec3 const &camera_pos)
    {
        if (active_ == WidgetType::rotate)
        {
            auto hit = PlaneHit(pos, click_dir, camera_pos);
            drag_end_ = glm::normalize(hit - pos);

            float angle = std::acos(glm::dot(drag_start_, drag_end_));
            float sign = math::Sign(glm::cross(drag_start_, drag_end_)[(int)axis_]);

            glm::vec3 euler{};
            euler[(int)axis_] = sign * glm::degrees(angle);
            rotation_degrees_ = euler[(int)axis_];
            drag_start_ = drag_end_;
            drag_end_ = euler;
        }
        else
        {
            auto hit = AxisHit(pos, click_dir, camera_pos);
            if (active_ == WidgetType::scale)
            {
                drag_end_ = glm::vec3{1.0f};
                drag_end_[(int)axis_] = glm::length(hit - pos) / glm::length(drag_start_ - pos);
                drag_start_ = hit;
            }
            else
            {
                drag_start_ = drag_end_;
                drag_end_ = hit;
            }
        }
    }

    void Widgets::EndDrag()
    {
        dragging_ = false;
        drag_start_ = drag_end_ = {};
    }

    scene::Pose Widgets::ApplyAction(scene::Pose const &old_pose)
    {
        scene::Pose new_pose{old_pose};
        switch (active_)
        {
        case WidgetType::move:
        {
            new_pose.pos_ = drag_end_ - drag_start_ + old_pose.pos_;
            break;
        }
        case WidgetType::rotate:
        {
            new_pose.euler_ = new_pose.euler_ + drag_end_;
            break;
        }
        case WidgetType::scale:
        {
            auto rot = glm::eulerAngleXYZ(old_pose.euler_.x, old_pose.euler_.y, old_pose.euler_.z);
            auto transform = glm::inverse(rot) * glm::scale(drag_end_) * rot * glm::scale(old_pose.scale_);
            new_pose.scale_ = {transform[0][0], transform[1][1], transform[2][2]};
            break;
        }
        default:
            break;
        }
        return new_pose;
    }
    glm::vec3 Widgets::AxisHit(glm::vec3 const &pos, glm::vec3 const &click_dir, glm::vec3 const &camera_pos)
    {
        glm::vec3 active_axis{0.0f}, f_axis{0.0f}, s_axis{0.0f};

        active_axis[(int)axis_] = 1.0f;
        f_axis[((int)axis_ + 1) % 3] = 1.0f;
        s_axis[((int)axis_ + 2) % 3] = 1.0f;

        geometry::Plane f{pos, f_axis};
        geometry::Plane s{pos, s_axis};

        geometry::Line select{camera_pos, click_dir};
        geometry::Line move_axis{pos, active_axis};

        plane_selection_pos_f_ = f.Hit(select);
        plane_selection_pos_s_ = s.Hit(select);

        if (glm::length(plane_selection_pos_f_ - camera_pos) <=
            glm::length(plane_selection_pos_s_ - camera_pos))
            move_selection_pos_ = move_axis.ClosestTo(plane_selection_pos_f_);
        else
            move_selection_pos_ = move_axis.ClosestTo(plane_selection_pos_s_);

        return move_selection_pos_;
    }

    glm::vec3 Widgets::PlaneHit(glm::vec3 const &pos,
                                glm::vec3 const &click_dir,
                                glm::vec3 const &camera_pos)
    {
        glm::vec3 norm{0.0f};
        norm[(int)axis_] = 1.0f;
        geometry::Plane plane{pos, norm};
        geometry::Line select{camera_pos, click_dir};
        return plane_selection_pos_f_ = plane.Hit(select);
    }
}