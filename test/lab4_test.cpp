#include "gtest/gtest.h"
#include "../src/lab4/include/Figures.h"
#include <sstream>
#include <cmath>

using namespace std;

TEST(RectangleTest2, AreaCalculation) {
    Rectangle<double> rectangle;
    rectangle.vertices[0] = make_unique<Point<double>>(0, 0);
    rectangle.vertices[1] = make_unique<Point<double>>(4, 0);
    rectangle.vertices[2] = make_unique<Point<double>>(4, 3);
    rectangle.vertices[3] = make_unique<Point<double>>(0, 3);

    ASSERT_DOUBLE_EQ(rectangle.area(), 12.0);
}

TEST(RectangleTest2, CenterCalculation) {
    Rectangle<double> rectangle;
    rectangle.vertices[0] = make_unique<Point<double>>(0, 0);
    rectangle.vertices[1] = make_unique<Point<double>>(4, 0);
    rectangle.vertices[2] = make_unique<Point<double>>(4, 3);
    rectangle.vertices[3] = make_unique<Point<double>>(0, 3);

    auto center = rectangle.getCenter();
    ASSERT_DOUBLE_EQ(center.first, 2.0);
    ASSERT_DOUBLE_EQ(center.second, 1.5);
}

TEST(RectangleTest2, PrintOutput) {
    Rectangle<double> rectangle;
    rectangle.vertices[0] = make_unique<Point<double>>(0, 0);
    rectangle.vertices[1] = make_unique<Point<double>>(4, 0);
    rectangle.vertices[2] = make_unique<Point<double>>(4, 3);
    rectangle.vertices[3] = make_unique<Point<double>>(0, 3);

    stringstream ss;
    rectangle.print(ss);

    string expected_output = "Rectangle: (0, 0), (4, 0), (4, 3), (0, 3)";
    ASSERT_EQ(ss.str(), expected_output);
}

TEST(RectangleTest2, ReadInput) {
    stringstream input("0 0 4 0 4 3 0 3");
    Rectangle<double> rectangle;
    
    rectangle.read(input);

    ASSERT_DOUBLE_EQ(rectangle.vertices[0]->first, 0);
    ASSERT_DOUBLE_EQ(rectangle.vertices[0]->second, 0);
    ASSERT_DOUBLE_EQ(rectangle.vertices[1]->first, 4);
    ASSERT_DOUBLE_EQ(rectangle.vertices[1]->second, 0);
    ASSERT_DOUBLE_EQ(rectangle.vertices[2]->first, 4);
    ASSERT_DOUBLE_EQ(rectangle.vertices[2]->second, 3);
    ASSERT_DOUBLE_EQ(rectangle.vertices[3]->first, 0);
    ASSERT_DOUBLE_EQ(rectangle.vertices[3]->second, 3);
}

TEST(RhombusTest2, AreaCalculation) {
    Rhombus<double> rhombus;
    rhombus.vertices[0] = make_unique<Point<double>>(0, 0);
    rhombus.vertices[1] = make_unique<Point<double>>(4, 6);
    rhombus.vertices[2] = make_unique<Point<double>>(0, 12);
    rhombus.vertices[3] = make_unique<Point<double>>(-4, 6);

    ASSERT_DOUBLE_EQ(rhombus.area(), 48.0);
}

TEST(RhombusTest2, CenterCalculation) {
    Rhombus<double> rhombus;
    rhombus.vertices[0] = make_unique<Point<double>>(0, 0);
    rhombus.vertices[1] = make_unique<Point<double>>(4, 0);
    rhombus.vertices[2] = make_unique<Point<double>>(6, 4);
    rhombus.vertices[3] = make_unique<Point<double>>(2, 4);

    auto center = rhombus.getCenter();
    ASSERT_DOUBLE_EQ(center.first, 3.0);
    ASSERT_DOUBLE_EQ(center.second, 2.0);
}
