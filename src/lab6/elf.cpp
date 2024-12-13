#include "include/bear.h"
#include "include/elf.h"
#include "include/bandit.h"

Elf::Elf(int x, int y) : NPC(ElfType, x, y) {}
Elf::Elf(std::istream &is) : NPC(ElfType, is) {}

void Elf::print()
{
    std::cout << *this;
}

void Elf::save(std::ostream &os)
{
    os << ElfType << std::endl;
    NPC::save(os);
}

void Elf::accept(FightVisitor &visitor) {
    visitor.visit(std::dynamic_pointer_cast<Elf>(shared_from_this()));
}

bool Elf::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, false); // Elves do not kill Bears
    return false;
}

bool Elf::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, false); // Elves do not kill Elves
    return false;
}

bool Elf::fight(std::shared_ptr<Bandit> other) {
    fight_notify(other, true); // Elves kill Bandits
    return true;
}

std::ostream &operator<<(std::ostream &os, Elf &elf)
{
    os << "elf: " << *static_cast<NPC *>(&elf) << std::endl;
    return os;
}