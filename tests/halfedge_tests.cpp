#include "gtest/gtest.h"
#include "geometry/mesh.hpp"
#include "geometry/halfedge_mesh.hpp"

int main()
{
    testing::InitGoogleTest();
    [[maybe_unused]] int a{RUN_ALL_TESTS()};
}

TEST(HalfEdge, construct_from_mesh)
{
    auto mesh{gl::Mesh{{{glm::vec3{-4, -4, -0}, {0, 0, 0}, 0},
                        {glm::vec3{4, -4, -0}, {0, 0, 0}, 0},
                        {glm::vec3{4, 4, -0}, {0, 0, 0}, 0},
                        {glm::vec3{-4, 4, -0}, {0, 0, 0}, 0}},
                       {0, 1, 2, 2, 3, 0}}};
    geometry::HalfedgeMesh hmesh{};
    hmesh.CreateFromMesh(std::move(mesh));
    EXPECT_EQ(hmesh.vertices_.size(), 4);
    EXPECT_EQ(hmesh.edges_.size(), 5);
    EXPECT_EQ(hmesh.faces_.size(), 3);
    EXPECT_EQ(hmesh.halfedges_.size(), 10);
}