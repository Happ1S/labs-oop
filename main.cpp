#include <iostream>
#include <vector>
#include <memory>
#include "./src/lab3/include/Rectangle.h"
#include "./src/lab3/include/Rhombus.h"
#include "./src/lab3/include/Trapeze.h"

void printMenu() {
    std::cout << "Меню:\n";
    std::cout << "1. Добавить фигуру\n";
    std::cout << "2. Показать все фигуры\n";
    std::cout << "3. Общая площадь всех фигур\n";
    std::cout << "4. Удалить фигуру\n";
    std::cout << "5. Выход\n";
    std::cout << "Выберите действие: ";
}

void addFigure(std::vector<std::unique_ptr<Figure>>& figures) {
    int choice;
    std::cout << "1. Прямоугольник\n2. Ромб\n3. Трапеция\nВыберите тип фигуры: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            figures.push_back(std::make_unique<Rectangle>());
            break;
        case 2:
            figures.push_back(std::make_unique<Rhombus>());
            break;
        case 3:
            figures.push_back(std::make_unique<Trapeze>());
            break;
        default:
            std::cout << "Неверный выбор!\n";
            return;
    }

    std::cout << "Введите данные для фигуры:\n";
    std::cin >> *figures.back();
}

void printFigures(const std::vector<std::unique_ptr<Figure>>& figures) {
    if (figures.empty()) {
        std::cout << "Нет доступных фигур.\n";
        return;
    }

    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << *figures[i]; 
        std::cout << "\n";
        auto center = figures[i]->getCenter();
        std::cout << "Геометрический центр: (" << center.first << ", " << center.second << ")\n";
        std::cout << "Площадь: " << static_cast<double>(*figures[i]) << "\n";
    }
}

double totalArea(const std::vector<std::unique_ptr<Figure>>& figures) {
    double total = 0;
    for (const auto& figure : figures) {
        total += static_cast<double>(*figure);
    }
    return total;
}

void deleteFigure(std::vector<std::unique_ptr<Figure>>& figures) {
    if (figures.empty()) {
        std::cout << "Нет фигур для удаления.\n";
        return;
    }

    int index;
    std::cout << "Введите индекс фигуры для удаления: ";
    std::cin >> index;

    if (index >= 0 && index <= static_cast<int>(figures.size()) - 1) {
        figures.erase(figures.begin() + index);
        std::cout << "Фигура удалена!\n";
    } else {
        std::cout << "Неверный индекс!\n";
    }
}

int main() {
    std::vector<std::unique_ptr<Figure>> figures;
    bool exitMenu = false;

    while (!exitMenu) {
        printMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                addFigure(figures);
                break;
            case 2:
                printFigures(figures);
                break;
            case 3:
                std::cout << "Общая площадь всех фигур: " << totalArea(figures) << "\n";
                break;
            case 4:
                deleteFigure(figures);
                break;
            case 5:
                exitMenu = true;
                break;
            default:
                std::cout << "Неверный выбор! Попробуйте снова.\n";
                break;
        }

        std::cout << "Нажмите Enter для продолжения...\n";
        std::cin.ignore(); 
        std::cin.get();    
    }

    return 0;
}
