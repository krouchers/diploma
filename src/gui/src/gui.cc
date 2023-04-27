#include "gui/gui.hpp"
#include "utils/log.hpp"
#include "opengl.hpp"
#include "SDL.h"

#include "utils/generate_primitives.hpp"

#include "geometry/halfedge_mesh.hpp"

#include "scene/renderer.hpp"
#include "scene/scene.hpp"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

DearGui::DearGui(std::shared_ptr<Opengl> &gl,
                 std::shared_ptr<IWindow> &window,
                 std::shared_ptr<Camera> &cam,
                 std::string const &exe_path)
    : window_{window}, gl_{gl}, camera_{cam}
{
    info("Initializing DearGui...");

    ImGui::CreateContext();
    auto &io{ImGui::GetIO()};
    io.Fonts->AddFontFromFileTTF(
        std::filesystem::path{exe_path}.parent_path().parent_path().append("fonts").append("Anonymous_Pro.ttf").string().c_str(), 16.0f,
        nullptr, io.Fonts->GetGlyphRangesCyrillic());

    ImGui_ImplSDL2_InitForOpenGL(
        reinterpret_cast<SDL_Window *>(window_->GetHandler()),
        reinterpret_cast<SDL_GLContext *>(gl_->GetHandler()));
    ImGui_ImplOpenGL3_Init(nullptr);
}

void DearGui::AddSlider(const std::string &name, float &value)
{
    ImGui::SliderFloat(name.c_str(), &value, 0.0f, 1.0f, "ratio = %.3f");
}

void DearGui::ProcessEvent(const Event &e)
{
    ImGui_ImplSDL2_ProcessEvent(reinterpret_cast<const SDL_Event *>(e.GetEventRawHandle()));
}

void DearGui::RenderUi()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    UIMenu();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DearGui::CreateBaseLine()
{
    int z, x;
    z = x = 20;
    float length{40};
    for (int i = -z; i <= z; ++i)
    {
        if (i == 0)
        {
            baseline_.Add({-length / 2, 0, i}, {length / 2, 0, i}, {Color::red});
            continue;
        }
        baseline_.Add({-length / 2, 0, i}, {length / 2, 0, i}, {Color::baseplane});
    }

    for (int i = -x; i <= x; ++i)
    {
        if (i == 0)
        {
            baseline_.Add({i, 0, -length / 2}, {i, 0, length / 2}, {Color::blue});
            continue;
        }
        baseline_.Add({i, 0, -length / 2}, {i, 0, length / 2}, {Color::baseplane});
    }
}

void DearGui::Render3D(Scene &scene)
{
    CreateBaseLine();

    scene.ForItems([&](scene::Item &item)
                   { item.Render(camera_->GetProjection() * camera_->GetView()); });

    scene::Renderer::Get().Lines(baseline_, camera_->GetProjection() * camera_->GetView());
}

void DearGui::UIMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::Button("Добавить фигуру"))
        {
            newObjWindow = true;
        }
        ImGui::EndMainMenuBar();
    }

    if (newObjWindow)
    {
        UINewObj();
    }
}

void DearGui::UINewObj()
{
    auto AddMesh{
        [](gl::Mesh &&mesh)
        {
            geometry::HalfedgeMesh hm{};
            hm.CreateFromMesh(std::move(mesh));
        }};
    ImGui::Begin("Добавить фигуру", &newObjWindow);
    if (ImGui::CollapsingHeader("Куб"))
    {
        static float edgeLenght{};
        ImGui::SliderFloat("Длина ребра", &edgeLenght, 1.0f, 10.0f);
        if (ImGui::Button("Добавить"))
        {
            auto [verts, inds]{utils::GenerateCube(edgeLenght / 2)};
            AddMesh(gl::Mesh{std::move(verts), std::move(inds)});
        }
    }
    ImGui::End();
}