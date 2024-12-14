#include "include/bear.h"
#include "include/elf.h"
#include "include/bandit.h"
#include "include/fight_visitor.h"

Bear::Bear(int x, int y) : NPC(BearType, x, y) {}
Bear::Bear(std::istream &is) : NPC(BearType, is) {}

void Bear::print() {
    std::cout << *this;
}

void Bear::accept(FightVisitor &visitor) {
    visitor.visit(std::static_pointer_cast<Bear>(shared_from_this()));
}

void Bear::save(std::ostream &os) {
    os << BearType << std::endl;
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

bool Bear::fight(std::shared_ptr<NPC> other) {
    FightExecutor executor;
    other->accept(executor);
    fight_notify(other, executor.success);
    return executor.success;
}

std::ostream &operator<<(std::ostream &os, Bear &bear) {
    os << "bear: " << *static_cast<NPC *>(&bear) << std::endl;
    return os;
}