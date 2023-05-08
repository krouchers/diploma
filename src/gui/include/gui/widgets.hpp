#pragma once

#include <scene/item.hpp>

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
        void Render(const glm::vec3 &pos, float scale);

        scene::Item x_move;
        scene::Item y_move;
        scene::Item z_move;

        WidgetType active_{WidgetType::move};
        Axis axis_{Axis::X};

        bool dragging_;
    };
}