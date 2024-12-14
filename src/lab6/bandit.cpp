#include "include/bear.h"
#include "include/elf.h"
#include "include/bandit.h"

Bandit::Bandit(int x, int y) : NPC(BanditType, x, y) {}
Bandit::Bandit(std::istream &is) : NPC(BanditType, is) {}

void Bandit::print() {
    std::cout << *this;
}

void Bandit::save(std::ostream &os) {
    os << BanditType << std::endl;
    NPC::save(os);
}

bool Bandit::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, false); // Bandits do not kill Bears
    return false;
}

bool Bandit::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, false); // Bandits do not kill Elves
    return false;
}

bool Bandit::fight(std::shared_ptr<Bandit> other) {
    fight_notify(other, true); // Bandits kill Bandits
    return true;
}

std::ostream &operator<<(std::ostream &os, Bandit &bandit) {
    os << "bandit: " << *static_cast<NPC *>(&bandit) << std::endl;
    return os;
}