#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"

class Rhombus : public Figure {
protected:
    double x1, y1, x2, y2, x3, y3, x4, y4;

public:
    
    Rhombus() : x1(0), y1(0), x2(0), y2(0), x3(0), y3(0), x4(0), y4(0) {}
    Rhombus(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
        : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), x4(x4), y4(y4) {}

    Rhombus(const Rhombus& other) = default;
    Rhombus(Rhombus&& other) noexcept = default;
    Rhombus& operator=(const Rhombus& other) = default;
    Rhombus& operator=(Rhombus&& other) noexcept = default;
    bool operator==(const Rhombus& other) const {
        return x1 == other.x1 && y1 == other.y1 &&
               x2 == other.x2 && y2 == other.y2 &&
               x3 == other.x3 && y3 == other.y3 &&
               x4 == other.x4 && y4 == other.y4;
    }

    std::pair<double, double> getCenter() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    friend std::ostream& operator<<(std::ostream& os, const Rhombus& rhombus);
    friend std::istream& operator>>(std::istream& is, Rhombus& rhombus);
};

#endif
