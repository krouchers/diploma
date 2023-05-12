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
    X = 0,
    Y,
    Z
};

namespace gui
{
    struct Widgets
    {
        Widgets();
        void Select(SceneID);
        glm::vec3 AxisHit(glm::vec3 const &pos,
                          glm::vec3 const &click_dir,
                          glm::vec3 const &camera_pos);
        glm::vec3 PlaneHit(glm::vec3 const &pos,
                          glm::vec3 const &click_dir,
                          glm::vec3 const &camera_pos);
        void Render(const glm::vec3 &pos, float scale);
        void StartDrag(glm::vec3 const &pos,
                       glm::vec3 const &click_dir,
                       glm::vec3 const &camera_pos);
        void DragTo(glm::vec3 const &pos,
                    glm::vec3 const &click_dir,
                    glm::vec3 const &camera_pos);
        scene::Pose ApplyAction(scene::Pose const &old_pose);
        void EndDrag();

        scene::Item x_move_;
        scene::Item y_move_;
        scene::Item z_move_;

        scene::Item x_rot_;
        scene::Item y_rot_;
        scene::Item z_rot_;

        scene::Item x_scale_;
        scene::Item y_scale_;
        scene::Item z_scale_;

        WidgetType active_{WidgetType::move};
        Axis axis_{Axis::X};

        bool dragging_{false};

        glm::vec3 drag_start_, drag_end_;

        // debug section
        glm::vec3 move_selection_pos_;
        glm::vec3 plane_selection_pos_f_;
        glm::vec3 plane_selection_pos_s_;
        float rotation_degrees_;
        //
    };
}