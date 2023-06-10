#include "gtest/gtest.h"

#include "geometry/line.hpp"
#include "geometry/plane.hpp"

TEST(PlaneTest, IntersectionWithLine)
{
    using namespace geometry;

    Line line1{{2.f, 0.f, 0.f}, {0.f, 1.f, 0.f}};   // Инициализируем линию
    Plane plane1{{0.f, 1.f, 0.f}, {0.f, 1.f, 0.f}}; // Инициализируем плоснкость

    glm::vec3 expected1{2.f, 1.f, 0.f};      // Ожидаем получить
    EXPECT_EQ(plane1.Hit(line1), expected1); // Проверяем на совпадение

    // Аналогично, но с другими значениями
    Line line2{{1.f, 2.f, 3.f}, {2.f, 1.f, -1.f}};
    Plane plane2{{0.f, 0.f, 1.f}, {1.f, -2.f, 1.f}};

    glm::vec3 expected2{-1.f, 1.f, 4.f};
    EXPECT_EQ(plane2.Hit(line2), expected2);
}

// Тест корректности вычисления ближайшей точки на линии к данной точке.
TEST(LineTest, ClosestTo)
{
    using namespace geometry;

    Line line{{0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}};
    glm::vec3 expected{1.f, 0.f, 0.f};
    EXPECT_EQ(line.ClosestTo({1.f, 1.f, 0.f}), expected);
}