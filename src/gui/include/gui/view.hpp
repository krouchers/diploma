#pragma once

#include "gui/Problem.hpp"
#include "scene/scene.hpp"

#include <optional>

class View
{
public:
    size_t &GetCurrentProblemId();
    std::vector<Problem> &GetProblems();
    std::vector<std::string> &GetProblemsNames();
    void SelectProblem(size_t id);
    void AddProblem(const char *name, const char *text, geometry::Mesh &mesh);
    void Render();

    char problem_name[128]{};
    char problem_text[1028]{};

private:
    size_t next_id{0};

    // data for current porblem
    std::string problem_name_;
    std::string problem_text_;
    geometry::Mesh problem_mesh_;

    std::vector<Problem> problems_;
    std::vector<std::string> problem_names_;
    std::optional<size_t> current_item_id_;
};