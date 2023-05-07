#include "gtest/gtest.h"
#include "geometry/mesh.hpp"
#include "geometry/halfedge_mesh.hpp"
#include "utils/generate_primitives.hpp"

int main()
{
    testing::InitGoogleTest();
    [[maybe_unused]] int a{RUN_ALL_TESTS()};
}

TEST(HalfEdge, construct_from_mesh_plane)
{
    utils::Data data{{{glm::vec3{-4, -4, -0}, {0, 0, 0}, 0},
                      {glm::vec3{4, -4, -0}, {0, 0, 0}, 0},
                      {glm::vec3{4, 4, -0}, {0, 0, 0}, 0},
                      {glm::vec3{-4, 4, -0}, {0, 0, 0}, 0}},
                     {0, 1, 2, 2, 3, 0}};
    geometry::HalfedgeMesh hmesh{};
    hmesh.CreateFromData(std::move(data));
    EXPECT_EQ(hmesh.vertices_.size(), 4);
    EXPECT_EQ(hmesh.edges_.size(), 5);
    EXPECT_EQ(hmesh.faces_.size(), 3);
    EXPECT_EQ(hmesh.halfedges_.size(), 10);
}

TEST(HalfEdge, construct_from_mesh_cube)
{
    utils::Data data{{{glm::vec3{-5, -5, -5}, {0, 0, 0}, 0},
                      {glm::vec3{5, -5, -5}, {0, 0, 0}, 0},
                      {glm::vec3{5, 5, -5}, {0, 0, 0}, 0},
                      {glm::vec3{-5, 5, -5}, {0, 0, 0}, 0},
                      {glm::vec3{-5, -5, 5}, {0, 0, 0}, 0},
                      {glm::vec3{5, -5, 5}, {0, 0, 0}, 0},
                      {glm::vec3{5, 5, 5}, {0, 0, 0}, 0},
                      {glm::vec3{-5, 5, 5}, {0, 0, 0}, 0}},
                     {0, 1, 3, 3, 1, 2, 1, 5, 2, 2, 5, 6, 5, 4, 6, 6, 4, 7,
                      4, 0, 7, 7, 0, 3, 3, 2, 7, 7, 2, 6, 4, 5, 0, 0, 5, 1}};
    geometry::HalfedgeMesh hmesh{};
    hmesh.CreateFromData(std::move(data));
    EXPECT_EQ(hmesh.vertices_.size(), 8);
    EXPECT_EQ(hmesh.edges_.size(), 18);
    EXPECT_EQ(hmesh.faces_.size(), 12);
    EXPECT_EQ(hmesh.halfedges_.size(), 36);

    for (auto i{hmesh.halfedges_.begin()}; i != hmesh.halfedges_.end(); ++i)
    {
        std::pair expected{i->twin_->pair.second, i->twin_->pair.first};
        EXPECT_EQ(i->pair, expected);
    }

    for (auto i{hmesh.faces_.begin()}; i != hmesh.faces_.end(); ++i)
    {
        auto h{i->halfedge_};
        for (size_t j{0}; j < 3; ++j)
        {
            h = h->next_;
        }
        EXPECT_EQ(h, i->halfedge_);
    }
}
