#include "../../include/Octal.h"
#include <cstring>
#include <algorithm>
#include <stdexcept>  

Octal::Octal() : _digits(nullptr), _capacity(0), size(0) {}


Octal::Octal(const size_t& n, unsigned char t) : _capacity(n), size(n) {
    _digits = new unsigned char[_capacity];
    for (size_t i = 0; i < size; ++i) {
        _digits[i] = t;
    }
}

Octal::Octal(const std::initializer_list<unsigned char>& t) : _capacity(t.size()), size(t.size()) {
    _digits = new unsigned char[_capacity];
    size_t i = 0;
    for (auto& val : t) {
        if (val > 7) throw std::invalid_argument("Not valid digit");
        _digits[i++] = val;
    }
}


Octal::Octal(const std::string& t) {
    size = t.size();
    _capacity = size;
    _digits = new unsigned char[_capacity];
    for (size_t i = 0; i < size; ++i) {
        _digits[i] = t[i] - '0';
    }
}


Octal::Octal(const Octal& other) : _capacity(other._capacity), size(other.size) {
    _digits = new unsigned char[_capacity];
    for (size_t i = 0; i < size; ++i) {
            _digits[i] = other._digits[i];
    }
}


Octal::Octal(Octal&& other) noexcept : _digits(other._digits), _capacity(other._capacity), size(other.size) {
    other._digits = nullptr;
    other.size = 0;
    other._capacity = 0;
}


Octal::~Octal() noexcept {
    delete[] _digits;
}

size_t Octal::getSize() const {
    return size;
}

void Octal::print() const {
    for (size_t i = 0; i < size; ++i) {
        std::cout << static_cast<int>(_digits[i]);
    }
    std::cout << std::endl;
}

Octal Octal::add(const Octal& other) const {
    size_t maxSize = std::max(size, other.size);
    size_t newSize = maxSize + 1;

    Octal result(newSize, 0);

    int carry = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        int digit1 = static_cast<int>((i < size) ? _digits[size - 1 - i] : 0);
        int digit2 = static_cast<int>((i < other.size) ? other._digits[other.size - 1 - i] : 0);
        int sum = digit1 + digit2 + carry;
        result._digits[i] = static_cast<unsigned char>(sum % 8);
        carry = sum / 8;
    }

    if (carry > 0) {
        result._digits[0] = carry;
    } else {
        result.size = maxSize;
    }
    result.reverse();

    return result;
}

Octal Octal::subtract(const Octal& other) const {
    if (size < other.size) {
        throw std::invalid_argument("Error");
    }

    size_t maxSize = size;

    Octal result(maxSize, 0);

    int borrow = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        int digit1 = static_cast<int>((i < size) ? _digits[size - 1 - i] : 0);
        int digit2 = static_cast<int>((i < other.size) ? other._digits[other.size - 1 - i] : 0);
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 8;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result._digits[i] = static_cast<unsigned char>(diff);
    }

    size_t leadingZeros = 0;
    while (leadingZeros < result.size && result._digits[result.size - 1 - leadingZeros] == 0) {
        ++leadingZeros;
    }
    result.size -= leadingZeros;

    result.reverse();

    return result;
}

void Octal::copy(const Octal& other) {
    if (this != &other) {
        delete[] _digits;
        _capacity = other._capacity;
        size = other.size;
        _digits = new unsigned char[_capacity];
        for (size_t i = 0; i < size; ++i) {
            _digits[i] = other._digits[i];
        }
    }
}

void Octal::reverse() {
    std::reverse(_digits, _digits + size);
}

bool Octal::greater(const Octal& other) {
    if (size > other.size) {
        return true;
    } else if (size < other.size) {
        return false;
    } else {
         for (size_t i = 0; i < size; ++i) {
            if (_digits[i] > other._digits[i]) {
                return true;
            } else if (_digits[i] < other._digits[i]) {
                return false;
            }
        }
        return false;
    }
}

bool Octal::less(const Octal& other) {
    if (size > other.size) {
        return false;
    } else if (size < other.size) {
        return true;
    } else {
         for (size_t i = 0; i < size; ++i) {
            if (_digits[i] < other._digits[i]) {
                return true;
            } else if (_digits[i] > other._digits[i]) {
                return false;
            }
        }
        return false;
    }
}

bool Octal::equal(const Octal& other) {
    return !greater(other) & !less(other);
}