#include "gui/view.hpp"

size_t &View::GetCurrentProblemId()
{
    return current_item_id_.value();
}

std::vector<Problem> &View::GetProblems()
{
    return problems_;
}

std::vector<std::string> &View::GetProblemsNames()
{
    return problem_names_;
}

void View::AddProblem(const char *name, const char *text, geometry::Mesh &mesh)
{
    problems_.push_back({next_id++, name, text, std::move(mesh)});
    problem_names_.push_back(name);
}

void View::Render()
{
    if (current_item_id_.has_value())
        problems_[current_item_id_.value()].obj.Render();
}

void View::SelectProblem(size_t id)
{
    current_item_id_ = id;
}