#include "./include/Figures.h"
#include <cmath>

template <typename T>
std::pair<double, double> Rectangle<T>::getCenter() const {
    return { (this->vertices[0]->first + this->vertices[2]->first) / 2,
             (this->vertices[0]->second + this->vertices[2]->second) / 2 };
}

template <typename T>
double Rectangle<T>::area() const {
    return std::abs((this->vertices[1]->first - this->vertices[0]->first) *
                    (this->vertices[2]->second - this->vertices[1]->second));
}

template <typename T>
void Rectangle<T>::print(std::ostream& os) const {
    os << "Rectangle: ("
       << this->vertices[0]->first << ", " << this->vertices[0]->second << "), ("
       << this->vertices[1]->first << ", " << this->vertices[1]->second << "), ("
       << this->vertices[2]->first << ", " << this->vertices[2]->second << "), ("
       << this->vertices[3]->first << ", " << this->vertices[3]->second << ")";
}

template <typename T>
void Rectangle<T>::read(std::istream& is) {
    std::cout << "Enter the coordinates of the vertices of the rectangle: ";
    is >> this->vertices[0]->first >> this->vertices[0]->second
       >> this->vertices[1]->first >> this->vertices[1]->second
       >> this->vertices[2]->first >> this->vertices[2]->second
       >> this->vertices[3]->first >> this->vertices[3]->second;
}

template class Rectangle<double>;