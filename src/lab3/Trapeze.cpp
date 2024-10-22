#include "./include/Trapeze.h"
#include <cmath>

std::pair<double, double> Trapeze::getCenter() const {
    return {(x1 + x2 + x3 + x4) / 4, (y1 + y2 + y3 + y4) / 4};
}

double Trapeze::area() const {
    if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0 &&
        x3 == 0 && y3 == 0 && x4 == 0 && y4 == 0) {
        return 0;
    }
    double base1 = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    double base2 = std::sqrt((x4 - x3) * (x4 - x3) + (y4 - y3) * (y4 - y3));
    double numerator = std::abs((x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1));
    double height = numerator / base1;
    return (base1 + base2) * height / 2;
}


void Trapeze::print(std::ostream& os) const {
    os << "Трапеция: (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << "), ("
       << x3 << ", " << y3 << "), (" << x4 << ", " << y4 << ")";
}

void Trapeze::read(std::istream& is) {
    std::cout << "Введите координаты 4 вершин трапеции: ";
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
}