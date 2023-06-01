#include "gui/view.hpp"

size_t &View::GetCurrentProblemId()
{
    return current_item_id_;
}

std::vector<Problem> &View::GetProblems()
{
    return problems_;
}

std::vector<std::string> &View::GetProblemsNames()
{
    return problem_names_;
}

void View::AddProblem(const char *name, const char *text, geometry::Mesh &&mesh)
{
    problems_.push_back({name, text, std::move(mesh)});
    problem_names_.push_back(name);
}