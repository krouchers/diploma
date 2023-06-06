#pragma once

using SceneID = unsigned int;

namespace gui
{
    enum class WidgetsIds : SceneID
    {
        none = 0,
        x_move,
        y_move,
        z_move,
        x_rot,
        y_rot,
        z_rot,
        x_scale,
        y_scale,
        z_scale,
        count
    };

    enum class Mode
    {
        layout,
        model,
        view
    };
}
