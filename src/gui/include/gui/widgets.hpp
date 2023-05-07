#pragma once

#include <scene/item.hpp>

using SceneID = unsigned int;

namespace gui
{
    class Widgets
    {
    public:
        Widgets();
        void Render(const glm::vec3 &pos, const glm::mat4x4 &view);

    private:
        scene::Item x_move;
        scene::Item y_move;
        scene::Item z_move;
    };
}