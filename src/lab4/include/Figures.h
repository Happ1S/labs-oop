#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <concepts>
#include <cmath>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <typename T>
struct Point {
    T first, second;
    Point(T x, T y) : first(x), second(y) {}
    bool operator==(const Point<T>& other) const {
        return (this->first == other.first && this->second == other.second);
    }
};

template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual std::pair<double, double> getCenter() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    std::vector<std::unique_ptr<Point<T>>> vertices;
    virtual operator double() const { return area(); }
    friend std::ostream& operator<<(std::ostream& os, const Figure& figure) {
        figure.print(os);
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Figure& figure) {
        figure.read(is);
        return is;
    }
};

template <class T>
class DynamicArray {
private:
    std::shared_ptr<T[]> data;  
    size_t size;                
    size_t capacity;            

public:
    DynamicArray() : size(0), capacity(10) {
        data = std::shared_ptr<T[]>(new T[capacity]);
    }

    void addFigure(const T& value) {
        if (size == capacity) {
            resize(capacity * 2);  
        }

        for (size_t i = size; i > 0; --i) {
            data[i] = data[i - 1];
        }

        data[0] = value;
        ++size;
    }

    void removeFigure(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }

        --size;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t get_size() const {
        return size;
    }

    size_t get_capacity() const {
        return capacity;
    }

    void printFigures() const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i]) {
                std::cout << *data[i] << std::endl;  
            }
        }
    }

    void printFigureCenters() const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i]) {
                std::cout << "Figure " << i + 1 << " center: " << data[i]->getFigureCenter().first << ", " << data[i]->getFigureCenter().second << std::endl;
            }
        }
    }

    void printVertices() const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i]) {
                std::cout << "Figure " << i + 1 << " vertices: ";
                for (const auto& vertex : (*data[i]).vertices) {
                    std::cout << "(" << vertex->first << ", " << vertex->second << ") ";
                }
                std::cout << std::endl;
            }
        }
    }

    void printAreas() const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i]) {
                std::cout << "Figure " << i + 1 << " area: " << data[i]->getArea() << std::endl;
            }
        }
    }

    double totalArea() const {
        double total = 0.0;
        for (size_t i = 0; i < size; ++i) {
            if (data[i]) {
                total += data[i]->getArea(); 
            }
        }
        return total;
    }

private:
    void resize(size_t new_capacity) {
        if (new_capacity <= capacity) {
            return;
        }

        std::shared_ptr<T[]> new_data = std::shared_ptr<T[]>(new T[new_capacity]);

        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }

        data = new_data;
        capacity = new_capacity;
    }
};

template <typename T>
class Rectangle : public Figure<T> {
public:
    Rectangle() {
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
    }

    std::pair<double, double> getCenter() const ;

    double area() const ;

    void print(std::ostream& os) const ;

    void read(std::istream& is) ;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Rectangle<U>& rectangle);

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Rectangle<U>& rectangle);
};

template <typename T>
class Rhombus : public Figure<T> {
public:
    Rhombus() {
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
    }

    Rhombus(const Rhombus& other) = default;
    Rhombus(Rhombus&& other) noexcept = default;
    Rhombus& operator=(const Rhombus& other) = default;
    Rhombus& operator=(Rhombus&& other) noexcept = default;
    bool operator==(const Rhombus& other) const {
        return *this->vertices[0] == *other.vertices[0] &&
               *this->vertices[1] == *other.vertices[1] &&
               *this->vertices[2] == *other.vertices[2] &&
               *this->vertices[3] == *other.vertices[3];
    }

    std::pair<double, double> getCenter() const ;

    double area() const ;

    void print(std::ostream& os) const ;

    void read(std::istream& is) ;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Rhombus<U>& rhombus);

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Rhombus<U>& rhombus);
};

template <typename T>
class Trapeze : public Figure<T> {
public:
    Trapeze() {
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
        this->vertices.emplace_back(std::make_unique<Point<T>>(0, 0));
    }

    Trapeze(const Trapeze& other) = default;
    Trapeze(Trapeze&& other) noexcept = default;
    Trapeze& operator=(const Trapeze& other) = default;
    Trapeze& operator=(Trapeze&& other) noexcept = default;
    bool operator==(const Trapeze& other) const {
        return *this->vertices[0] == *other.vertices[0] &&
               *this->vertices[1] == *other.vertices[1] &&
               *this->vertices[2] == *other.vertices[2] &&
               *this->vertices[3] == *other.vertices[3];
    }

    std::pair<double, double> getCenter() const ;

    double area() const ;

    void print(std::ostream& os) const ;

    void read(std::istream& is) ;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Trapeze<U>& trapezoid);

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Trapeze<U>& trapezoid);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Rectangle<T>& rectangle) {
    rectangle.print(os);
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Rectangle<T>& rectangle) {
    rectangle.read(is);
    return is;
}

#endif