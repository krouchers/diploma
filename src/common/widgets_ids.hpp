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
        count
    };
}