#include "./include/Figures.h"
#include <cmath>

template <typename T>
std::pair<double, double> Rhombus<T>::getCenter() const {
    return { (this->vertices[0]->first + this->vertices[1]->first +
              this->vertices[2]->first + this->vertices[3]->first) / 4,
             (this->vertices[0]->second + this->vertices[1]->second +
              this->vertices[2]->second + this->vertices[3]->second) / 4 };
}

template <typename T>
double Rhombus<T>::area() const {
    double d1 = std::sqrt(std::pow(this->vertices[2]->first - this->vertices[0]->first, 2) +
                          std::pow(this->vertices[2]->second - this->vertices[0]->second, 2));

    double d2 = std::sqrt(std::pow(this->vertices[3]->first - this->vertices[1]->first, 2) +
                          std::pow(this->vertices[3]->second - this->vertices[1]->second, 2));

    return (d1 * d2) / 2;
}

template <typename T>
void Rhombus<T>::print(std::ostream& os) const {
    os << "Rhombus: ("
       << this->vertices[0]->first << ", " << this->vertices[0]->second << "), ("
       << this->vertices[1]->first << ", " << this->vertices[1]->second << "), ("
       << this->vertices[2]->first << ", " << this->vertices[2]->second << "), ("
       << this->vertices[3]->first << ", " << this->vertices[3]->second << ")";
}

template <typename T>
void Rhombus<T>::read(std::istream& is) {
    std::cout << "Введите координаты 4 вершин ромба: ";
    is >> this->vertices[0]->first >> this->vertices[0]->second
       >> this->vertices[1]->first >> this->vertices[1]->second
       >> this->vertices[2]->first >> this->vertices[2]->second
       >> this->vertices[3]->first >> this->vertices[3]->second;
}

template class Rhombus<double>;