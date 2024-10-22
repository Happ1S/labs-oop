#include "./include/Rhombus.h"
#include <cmath>

std::pair<double, double> Rhombus::getCenter() const {
    return {(x1 + x2 + x3 + x4) / 4, (y1 + y2 + y3 + y4) / 4};
}

double Rhombus::area() const {
    double d1 = std::sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
    double d2 = std::sqrt((x4 - x2) * (x4 - x2) + (y4 - y2) * (y4 - y2));
    return d1 * d2 / 2;
}


void Rhombus::print(std::ostream& os) const {
    os << "Ромб: (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << "), ("
       << x3 << ", " << y3 << "), (" << x4 << ", " << y4 << ")";
}

void Rhombus::read(std::istream& is) {
    std::cout << "Введите координаты 4 вершин ромба: ";
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
}
