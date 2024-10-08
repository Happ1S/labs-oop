#include <iostream>
#include "include/Octal.h"

int main()
{
    Octal octal1("123");
    Octal octal2("456");
    Octal octal3 = octal1;
    bool a = octal1.less(octal2);
    std::cout << "123 < 456 : " << a << std::endl;
    bool b = octal1.equal(octal2);
    std::cout << "123 == 456 : " << b << std::endl;
    bool c = octal1.greater(octal2);
    std::cout << "123 > 456 : " << c << std::endl;
    Octal sum = octal1.add(octal2);
    std::cout << "123 + 456 = ";
    sum.print();
    std::cout << "456 - 123 = ";
    Octal diff = octal2.subtract(octal1);
    diff.print();
    return 0;
}