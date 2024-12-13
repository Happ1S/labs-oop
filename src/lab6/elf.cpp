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

bool Elf::accept(const std::shared_ptr<NPC>& attacker) {
    if (auto elf = std::dynamic_pointer_cast<Bandit>(attacker)) {
        return attacker->fight(shared_from_this());
    }
    return false;
}

bool Elf::fight(std::shared_ptr<Bear> other)
{
    fight_notify(other, true);
    return true;
}

bool Elf::fight(std::shared_ptr<Elf> other)
{
    fight_notify(other, true);
    return true;
}

bool Elf::fight(std::shared_ptr<Bandit> other)
{
    fight_notify(other, true);
    return true;
}

std::ostream &operator<<(std::ostream &os, Elf &elf)
{
    os << "elf: " << *static_cast<NPC *>(&elf) << std::endl;
    return os;
}