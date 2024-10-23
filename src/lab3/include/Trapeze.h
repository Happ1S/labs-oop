#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"

class Trapeze : public Figure {
protected:
    double x1, y1, x2, y2, x3, y3, x4, y4;

public:
    Trapeze() : x1(0), y1(0), x2(0), y2(0), x3(0), y3(0), x4(0), y4(0) {}
    Trapeze(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
        : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), x4(x4), y4(y4) {}

    
    Trapeze(const Trapeze& other) = default;
    Trapeze(Trapeze&& other) noexcept = default;

    std::pair<double, double> getCenter() const override;
    double area() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    friend std::ostream& operator<<(std::ostream& os, const Trapeze& trapezoid);
    friend std::istream& operator>>(std::istream& is, Trapeze& trapezoid);
        
    operator double() const { return area(); }
    Trapeze& operator=(const Trapeze& other) = default;
    Trapeze& operator=(Trapeze&& other) noexcept = default;
    bool operator==(const Trapeze& other) const {
        return x1 == other.x1 && y1 == other.y1 &&
               x2 == other.x2 && y2 == other.y2 &&
               x3 == other.x3 && y3 == other.y3 &&
               x4 == other.x4 && y4 == other.y4;
    }
};

#endif 
