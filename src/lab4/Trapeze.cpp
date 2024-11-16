#include "./include/Figures.h"
#include <cmath>

template <typename T>
std::pair<double, double> Trapeze<T>::getCenter() const {
    return { (this->vertices[0]->first + this->vertices[1]->first +
              this->vertices[2]->first + this->vertices[3]->first) / 4,
             (this->vertices[0]->second + this->vertices[1]->second +
              this->vertices[2]->second + this->vertices[3]->second) / 4 };
}

template <typename T>
double Trapeze<T>::area() const {
    if (*this->vertices[0] == *this->vertices[1] &&
        *this->vertices[1] == *this->vertices[2] &&
        *this->vertices[2] == *this->vertices[3]) {
        return 0;
    }
    double base1 = std::sqrt((this->vertices[1]->first - this->vertices[0]->first) *
                             (this->vertices[1]->first - this->vertices[0]->first) +
                             (this->vertices[1]->second - this->vertices[0]->second) *
                             (this->vertices[1]->second - this->vertices[0]->second));
    double base2 = std::sqrt((this->vertices[3]->first - this->vertices[2]->first) *
                             (this->vertices[3]->first - this->vertices[2]->first) +
                             (this->vertices[3]->second - this->vertices[2]->second) *
                             (this->vertices[3]->second - this->vertices[2]->second));
    double numerator = std::abs((this->vertices[2]->first - this->vertices[0]->first) *
                                (this->vertices[1]->second - this->vertices[0]->second) -
                                (this->vertices[1]->first - this->vertices[0]->first) *
                                (this->vertices[2]->second - this->vertices[0]->second));
    double height = numerator / base1;
    return (base1 + base2) * height / 2;
}

template <typename T>
void Trapeze<T>::print(std::ostream& os) const {
    os << "Trapeze: ("
       << this->vertices[0]->first << ", " << this->vertices[0]->second << "), ("
       << this->vertices[1]->first << ", " << this->vertices[1]->second << "), ("
       << this->vertices[2]->first << ", " << this->vertices[2]->second << "), ("
       << this->vertices[3]->first << ", " << this->vertices[3]->second << ")";
}

template <typename T>
void Trapeze<T>::read(std::istream& is) {
    std::cout << "Введите координаты 4 вершин трапеции: ";
    is >> this->vertices[0]->first >> this->vertices[0]->second
       >> this->vertices[1]->first >> this->vertices[1]->second
       >> this->vertices[2]->first >> this->vertices[2]->second
       >> this->vertices[3]->first >> this->vertices[3]->second;
}

template class Trapeze<double>;