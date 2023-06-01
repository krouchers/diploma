#include "gui/view.hpp"
#include "scene/renderer.hpp"

std::optional<size_t> &View::GetCurrentProblemId()
{
    return current_item_id_;
}

std::unordered_map<size_t, Problem> &View::GetProblems()
{
    return problems_;
}

void View::AddProblem(const char *name, const char *text, geometry::Mesh &mesh)
{
    problems_[next_id++] = {name, text, std::move(mesh)};
}

void View::Render()
{
    auto &r = scene::Renderer::Get();
    if (current_item_id_.has_value())
    {
        scene::Renderer::MeshOpts m_opts;
        m_opts.color_ = Color::white;
        r.Mesh(problems_[current_item_id_.value()].obj, m_opts);
    }
}

void View::SelectProblem(size_t id)
{
    current_item_id_ = id;
}

void View::DeleteProblem(size_t problem_id)
{
    problems_.erase(problem_id);
    current_item_id_.reset();
}