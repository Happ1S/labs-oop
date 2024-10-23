#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"

class Rectangle : public Figure {
protected:
    double x1, y1, x2, y2;

public:
    Rectangle() = default;
    Rectangle(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
    Rectangle(const Rectangle& other) = default;
    Rectangle(Rectangle&& other) noexcept = default;

    std::pair<double, double> getCenter() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    operator double() const { return area(); }
    Rectangle& operator=(const Rectangle& other) = default;
    Rectangle& operator=(Rectangle&& other) noexcept = default;
    bool operator==(const Rectangle& other) const {
        return x1 == other.x1 && y1 == other.y1 && x2 == other.x2 && y2 == other.y2;
    }
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle);
    friend std::istream& operator>>(std::istream& is, Rectangle& rectangle);

};

#endif
