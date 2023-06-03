#include "gui/view.hpp"
#include "scene/renderer.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

View::View(fs::path exe_path)
    : source_folder_{exe_path.parent_path().parent_path()}
{
    if (fs::exists(source_folder_ / "saves"))
    {
        for (const auto &entry : fs::directory_iterator{source_folder_ / "saves"})
        {
            Problem new_problem;

            std::ifstream input{entry.path().c_str()};
            std::string text_line;
            std::getline(input, text_line);

            new_problem.problem_name_ = text_line;
            while (std::getline(input, text_line) && text_line != "end")
            {
                new_problem.problem_text_.append(text_line);
                new_problem.problem_text_ += '\n';
            }

            std::string verts_data;
            std::stringstream sline(verts_data);
            while (std::getline(input, verts_data) && verts_data != "end")
            {
                sline = std::stringstream(verts_data);
                float v_x, v_y, v_z;
                float n_x, n_y, n_z;
                while (sline >> v_x && sline >> v_y && sline >> v_z && sline >> n_x && sline >> n_y && sline >> n_z)
                {
                    new_problem.obj.Vertices().push_back({{v_x, v_y, v_z}, {n_x, n_y, n_z}, 0});
                }
            }
            std::string inds_data;
            while (std::getline(input, inds_data) && inds_data != "end")
            {
                sline = std::stringstream(inds_data);
                size_t i;
                while (sline >> i)
                {
                    new_problem.obj.Indices().push_back(i);
                }
            }

            problems_[next_id++] = std::move(new_problem);
        }
    }
}

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
    auto file_path = fs::path{source_folder_ / "saves" / problems_[problem_id].problem_name_};
    if (fs::exists(file_path))
    {
        fs::remove(fs::path{source_folder_ / "saves" / problems_[problem_id].problem_name_}.c_str());
    }
    problems_.erase(problem_id);
    current_item_id_.reset();
}

void View::SaveProblemsToFiles()
{
    if (!fs::exists(source_folder_ / "saves"))
        fs::create_directories(source_folder_ / "saves");
    for (auto &[_, problem] : problems_)
    {
        if (!fs::exists(source_folder_ / "saves" / problem.problem_name_.c_str()))
        {
            std::ofstream out{source_folder_ / "saves" / problem.problem_name_.c_str()};
            out << problem.problem_name_ << std::endl;
            out << problem.problem_text_ << std::endl;
            out << "end" << std::endl;
            for (auto &v : problem.obj.Vertices())
            {
                out << v.pos.x << " " << v.pos.y << " " << v.pos.z << " ";
                out << v.norm.x << " " << v.norm.y << " " << v.norm.z << " ";
            }
            out << std::endl
                << "end" << std::endl;

            for (auto &i : problem.obj.Indices())
                out << i << " ";
            out << std::endl
                << "end" << std::endl;
        }
    }
}

View::~View()
{
    SaveProblemsToFiles();
}