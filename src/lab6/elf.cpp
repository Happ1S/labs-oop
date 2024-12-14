#include "include/bear.h"
#include "include/elf.h"
#include "include/bandit.h"
#include "include/fight_visitor.h"

Elf::Elf(int x, int y) : NPC(ElfType, x, y) {}
Elf::Elf(std::istream &is) : NPC(ElfType, is) {}

void Elf::print() {
    std::cout << *this;
}

void Elf::accept(FightVisitor &visitor) {
    visitor.visit(std::static_pointer_cast<Elf>(shared_from_this()));
}

void Elf::save(std::ostream &os) {
    os << ElfType << std::endl;
    NPC::save(os);
}

class FightExecutor : public FightVisitor {
public:
    bool success = false;

    void visit(std::shared_ptr<Bear> bear) override {
        // Custom logic for fighting a bear
        success = false;
    }

    void visit(std::shared_ptr<Elf> elf) override {
        // Custom logic for fighting an elf
        success = false;
    }

    void visit(std::shared_ptr<Bandit> bandit) override {
        // Custom logic for fighting another bandit
        success = true;
    }
};

bool Elf::fight(std::shared_ptr<NPC> other) {
    FightExecutor executor;
    other->accept(executor);
    fight_notify(other, executor.success);
    return executor.success;
}

std::ostream &operator<<(std::ostream &os, Elf &elf) {
    os << "elf: " << *static_cast<NPC *>(&elf) << std::endl;
    return os;
}