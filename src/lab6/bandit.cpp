#include "include/bear.h"
#include "include/elf.h"
#include "include/bandit.h"
#include "include/fight_visitor.h"

Bandit::Bandit(int x, int y) : NPC(BanditType, x, y) {}
Bandit::Bandit(std::istream &is) : NPC(BanditType, is) {}

void Bandit::print() {
    std::cout << *this;
}

void Bandit::accept(FightVisitor &visitor) {
    visitor.visit(std::static_pointer_cast<Bandit>(shared_from_this()));
}

void Bandit::save(std::ostream &os) {
    os << BanditType << std::endl;
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

bool Bandit::fight(std::shared_ptr<NPC> other) {
    FightExecutor executor;
    other->accept(executor);
    fight_notify(other, executor.success);
    return executor.success;
}

std::ostream &operator<<(std::ostream &os, Bandit &bandit) {
    os << "bandit: " << *static_cast<NPC *>(&bandit) << std::endl;
    return os;
}