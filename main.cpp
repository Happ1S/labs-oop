#include "src/lab6/include/npc.h"
#include "src/lab6/include/bear.h"
#include "src/lab6/include/elf.h"
#include "src/lab6/include/bandit.h"
#include "src/lab6/include/fight_visitor.h"
#include <fstream>
#include <set>
#include <memory>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iterator>

using set_t = std::set<std::shared_ptr<NPC>>;

// Text Observer
class TextObserver : public IFightObserver {
public:
    TextObserver() {}  // make it public

    static std::shared_ptr<IFightObserver> get() {
        static std::shared_ptr<TextObserver> instance = std::make_shared<TextObserver>();
        return instance;
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::cout << std::endl
                      << "Murder --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};


// Фабрики -----------------------------------
std::shared_ptr<NPC> factory(std::istream &is) {
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type) {
        switch (type) {
        case BearType:
            result = std::make_shared<Bear>(is);
            break;
        case ElfType:
            result = std::make_shared<Elf>(is);
            break;
        case BanditType:
            result = std::make_shared<Bandit>(is);
            break;
        default:
            std::cerr << "unexpected NPC type:" << type << std::endl;
            break;
        }
    } else {
        std::cerr << "Error reading NPC type." << std::endl;
    }

    if (result) {
        result->subscribe(TextObserver::get());
    }

    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y) {
    std::cout << "Type:" << (int)type << std::endl;
    std::shared_ptr<NPC> result;
    switch (type) {
    case BearType:
        result = std::make_shared<Bear>(x, y);
        break;
    case ElfType:
        result = std::make_shared<Elf>(x, y);
        break;
    case BanditType:
        result = std::make_shared<Bandit>(x, y);
        break;
    default:
        std::cerr << "Error: Unknown NPC type." << std::endl;
        break;
    }
    if (result) {
        result->subscribe(TextObserver::get());
    }

    return result;
}

// save array to file
void save(const set_t &array, const std::string &filename) {
    std::ofstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "Error opening file for saving: " << filename << std::endl;
        return;
    }

    fs << array.size() << std::endl;
    for (auto &n : array) {
        n->save(fs);
    }
    fs.flush();
    fs.close();
}

set_t load(const std::string &filename) {
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i) {
            auto npc = factory(is);
            if (npc) {
                result.insert(npc);
            } else {
                std::cerr << "Error loading NPC at index " << i << std::endl;
            }
        }
        is.close();
    } else {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    }
    return result;
}

// print to screen
std::ostream &operator<<(std::ostream &os, const set_t &array) {
    for (auto &n : array) {
        n->print();
    }
    return os;
}

// ВНИМАНИЕ: метод осуществляющий сражение написан неправильно!
// Переделайте его на использование паттерна Visitor
// То есть внутри цикла вместо кучи условий должно быть:
// success = defender->accept(attacker);
// В NPC методы типа is_dragon - станут не нужны

struct FightExecutor : public FightVisitor {
    std::shared_ptr<NPC> attacker;
    bool success = false;

    FightExecutor(std::shared_ptr<NPC> a) : attacker(a) {}

    void visit(std::shared_ptr<Bear> bear) override {
        if (attacker) {
            success = attacker->fight(bear);
        }
    }

    void visit(std::shared_ptr<Elf> elf) override {
        if (attacker) {
            success = attacker->fight(elf);
        }
    }

    void visit(std::shared_ptr<Bandit> bandit) override {
        if (attacker) {
            success = attacker->fight(bandit);
        }
    }
};

set_t fight(const set_t &array, size_t distance) {
    set_t dead_list;

    for (const auto &attacker : array) {
        for (const auto &defender : array) {
            if ((attacker != defender) && (attacker->is_close(defender, distance))) {
                if (attacker && defender) {
                    FightExecutor executor(attacker);
                    defender->accept(executor);
                    if (executor.success) {
                        dead_list.insert(defender);
                    }
                }
            }
        }
    }

    return dead_list;
}

int main() {
    set_t array; // монстры

    // Гененрируем начальное распределение монстров
    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 100; ++i) {
        array.insert(factory(NpcType(std::rand() % 3 + 1),
                             std::rand() % 100,
                             std::rand() % 100));
    }

    std::cout << "Saving ..." << std::endl;
    save(array, "npc.txt");

    std::cout << "Loading ..." << std::endl;
    array = load("npc.txt");

    std::cout << "Fighting ..." << std::endl
              << array;

    for (size_t distance = 20; (distance <= 100) && !array.empty(); distance += 10) {
        auto dead_list = fight(array, distance);
        for (auto &d : dead_list) {
            if (array.find(d) != array.end()) {
                array.erase(d);
            } else {
                std::cerr << "Error: NPC not found during removal." << std::endl;
            }
        }
        std::cout << "Fight stats ----------" << std::endl
                  << "distance: " << distance << std::endl
                  << "killed: " << dead_list.size() << std::endl
                  << std::endl
                  << std::endl;
    }

    std::cout << "Survivors:" << array;

    return 0;
}
