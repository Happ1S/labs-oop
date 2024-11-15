#include "src/lab5/include/memoryResource.h"
#include "src/lab5/include/linkinList.h"
#include "src/lab5/memoryResource.cpp"
#include "src/lab5/linkinList.tpp"
#include <iostream>
#include <string>

struct ComplexType {
    int id;
    double value;

    ComplexType(int i = 0, double v = 0.0)
        : id(i), value(v) {}
};
void test_with_int(MemoryResource& resource) {
    LinkedList<int> list(&resource);
    for (int i = 0; i < 5; ++i) {
        list.push_front(i);
    }

    std::cout << "Int linked list content:" << std::endl;
    for (const auto& item : list) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

void test_with_complex_type(MemoryResource& resource) {
    std::cout << "\nComplex content of linked list:\n";
    LinkedList<ComplexType> list(&resource);

    // Добавление элементов
    list.push_front(ComplexType(1, 1.1));
    list.push_front(ComplexType(2, 2.2));
    list.push_front(ComplexType(3, 3.3));

    // Вывод элементов
    for (const auto& item : list) {
        std::cout << "ID: " << item.id 
                  << ", Value: " << item.value << std::endl;

    }
}

int main() {
    MemoryResource resource;

    try {
        test_with_int(resource);
        test_with_complex_type(resource);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}