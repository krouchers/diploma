#pragma once

#include "gui/Problem.hpp"

class View
{
public:
    size_t &GetCurrentProblemId();
    std::vector<Problem> &GetProblems();
    std::vector<std::string> &GetProblemsNames();
    void AddProblem(const char *name, const char *text, geometry::Mesh &&mesh);

private:
    // size_t next_id{0};

    // data for current porblem
    std::string problem_name_;
    std::string problem_text_;
    geometry::Mesh problem_mesh_;

    std::vector<Problem> problems_;
    std::vector<std::string> problem_names_;
    size_t current_item_id_;
};