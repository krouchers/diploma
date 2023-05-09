#pragma once

#include "scene/item.hpp"
#include "scene/scene.hpp"
#include "scene/pose.hpp"

using SceneID = unsigned int;

enum class WidgetType
{
    move,
    rotate,
    scale,
    count
};

enum class Axis
{
    X,
    Y,
    Z
};

namespace gui
{
    struct Widgets
    {
        Widgets();
        void Select(SceneID);
        glm::vec3 AxisHit(scene::Pose const &pose,
                          glm::vec3 const &click_dir,
                          glm::vec3 const &camera_pos);
        void Render(const glm::vec3 &pos, float scale);
        void StartDrag(scene::Pose const &pose,
                       glm::vec3 const &click_dir,
                       glm::vec3 const &camera_pos);
        void DragTo(scene::Pose const &pose,
                    glm::vec3 const &click_dir,
                    glm::vec3 const &camera_pos);
        scene::Pose ApplyAction(scene::Pose const &old_pose);
        void EndDrag();

        scene::Item x_move;
        scene::Item y_move;
        scene::Item z_move;

        WidgetType active_{WidgetType::move};
        Axis axis_{Axis::X};

        bool dragging_{false};

        glm::vec3 drag_start_, drag_end_;

        // debug section
        glm::vec3 move_selection_pos_;
        glm::vec3 plane_selection_pos_f_;
        glm::vec3 plane_selection_pos_s_;
        //
    };
}