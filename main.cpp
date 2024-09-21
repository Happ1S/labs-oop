#include <iostream>
#include "lib.h"

int main()
{
    std::string sequence;
    std::cin >> sequence;
    std::cout << std::boolalpha << correct_parentheses_sequence(sequence) << std::endl;
    return 0;
}