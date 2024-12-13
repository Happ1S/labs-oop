#include "include/bear.h"
#include "include/elf.h"
#include "include/bandit.h"

Bear::Bear(int x, int y) : NPC(BearType, x, y) {}
Bear::Bear(std::istream &is) : NPC(BearType, is) {}

void Bear::print()
{
    std::cout << *this;
}

void Bear::save(std::ostream &os)
{
    os << BearType << std::endl;
    NPC::save(os);
}

void Bear::accept(FightVisitor &visitor) {
    visitor.visit(std::dynamic_pointer_cast<Bear>(shared_from_this()));
}

bool Bear::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, true);
    return true;
}

bool Bear::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, true); // Bears kill Elves
    return true;
}

bool Bear::fight(std::shared_ptr<Bandit> other) {
    fight_notify(other, false); // Bears do not kill Bandits
    return false;
}

std::ostream &operator<<(std::ostream &os, Bear &bear)
{
    os << "bear: " << *static_cast<NPC *>(&bear) << std::endl;
    return os;
}