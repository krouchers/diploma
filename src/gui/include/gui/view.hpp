#pragma once

#include "gui/Problem.hpp"
#include "scene/scene.hpp"

#include <optional>
#include <unordered_map>

class View
{
public:
    std::optional<size_t> &GetCurrentProblemId();
    std::unordered_map<size_t, Problem> &GetProblems();
    void SelectProblem(size_t id);
    void AddProblem(const char *name, const char *text, geometry::Mesh &mesh);
    void DeleteProblem(size_t problem_id);
    void Render();

    char problem_name[128]{};
    char problem_text[1028]{};

private:
    size_t next_id{0};

    // data for current porblem
    std::string problem_name_;
    std::string problem_text_;
    geometry::Mesh problem_mesh_;

    std::unordered_map<size_t, Problem> problems_;
    std::optional<size_t> current_item_id_;
};