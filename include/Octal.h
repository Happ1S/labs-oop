#ifndef OCTAL_H
#define OCTAL_H

#include <iostream>
#include <string>
#include <stdexcept>

class Octal {
public:
    size_t size;
    Octal();
    Octal(const size_t& n, unsigned char t = 0);
    Octal(const std::initializer_list<unsigned char>& t);
    Octal(const std::string& t);
    Octal(const Octal& other);
    Octal(Octal&& other) noexcept;

    virtual ~Octal() noexcept;

    void print() const;
    size_t getSize() const;
    Octal add(const Octal& other) const;
    Octal subtract(const Octal& other) const;
    void copy(const Octal& other);
    bool greater(const Octal& other);
    bool less(const Octal& other);
    bool equal(const Octal& other);

private:
    unsigned char* _digits;
    size_t _capacity;
    void reverse();
};

#endif
