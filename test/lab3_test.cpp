#include <gtest/gtest.h>
#include "../src/lab3/include/Rectangle.h"
#include "../src/lab3/include/Rhombus.h"
#include "../src/lab3/include/Trapeze.h"

TEST(RectangleTest, DefaultConstructor) {
    Rectangle rect;
    ASSERT_EQ(static_cast<double>(rect), 0);
}

TEST(RectangleTest, ParameterConstructor) {
    Rectangle rect(0, 0, 4, 3);
    ASSERT_EQ(static_cast<double>(rect), 12);
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle rect(1, 1, 5, 4);
    ASSERT_DOUBLE_EQ(static_cast<double>(rect), 12.0);
}

TEST(RectangleTest, CenterCalculation) {
    Rectangle rect(0, 0, 4, 4);
    auto center = rect.getCenter();
    ASSERT_DOUBLE_EQ(center.first, 2.0);
    ASSERT_DOUBLE_EQ(center.second, 2.0);
}

TEST(RhombusTest, DefaultConstructor) {
    Rhombus rhombus;
    ASSERT_EQ(static_cast<double>(rhombus), 0);
}

TEST(RhombusTest, ParameterConstructor) {
    Rhombus rhombus(0, 0, -1, 2, 0, 4, 1, 2);
    ASSERT_NEAR(static_cast<double>(rhombus), 4.0, 0.001);
}

TEST(RhombusTest, AreaCalculation) {
    Rhombus rhombus(0, 0, -1, 2, 0, 4, 1, 2);
    ASSERT_NEAR(static_cast<double>(rhombus), 4.0, 0.001);
}

TEST(RhombusTest, CenterCalculation) {
    Rhombus rhombus(0, 0, -1, 2, 0, 4, 1, 2);
    auto center = rhombus.getCenter();
    ASSERT_DOUBLE_EQ(center.first, 0.0);
    ASSERT_DOUBLE_EQ(center.second, 2.0);
}

TEST(TrapezeTest, DefaultConstructor) {
    Trapeze trapeze;
    ASSERT_EQ(static_cast<double>(trapeze), 0);
}

TEST(TrapezeTest, ParameterConstructor) {
    Trapeze trapeze(0, 0, 4, 0, 3, 3, 1, 3);
    ASSERT_NEAR(static_cast<double>(trapeze), 9.0, 0.001);
}

TEST(TrapezeTest, AreaCalculation) {
    Trapeze trapeze(0, 0, 4, 0, 3, 3, 1, 3);
    ASSERT_NEAR(static_cast<double>(trapeze), 9.0, 0.001);
}

TEST(TrapezeTest, CenterCalculation) {
    Trapeze trapeze(0, 0, 4, 0, 3, 3, 1, 3);
    auto center = trapeze.getCenter();
    ASSERT_DOUBLE_EQ(center.first, 2.0);
    ASSERT_DOUBLE_EQ(center.second, 1.5);
}
