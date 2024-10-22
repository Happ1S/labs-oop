#include "./include/Rectangle.h"
#include <cmath>

std::pair<double, double> Rectangle::getCenter() const {
    return {(x1 + x2) / 2, (y1 + y2) / 2};
}

double Rectangle::area() const {
    return std::abs((x2 - x1) * (y2 - y1));
}

void Rectangle::print(std::ostream& os) const {
    os << "Прямоугольник: (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")";
}

void Rectangle::read(std::istream& is) {
    std::cout << "Введите координаты 2 вершин прямоугольника: ";
    is >> x1 >> y1 >> x2 >> y2;
}