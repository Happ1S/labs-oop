#include "include/bandit.h"
#include "include/visitor.h"

Bandit::Bandit(int x, int y) : NPC(x, y, "Bandit") {}

Bandit::Bandit(std::istream &is) : NPC(is) {}

void Bandit::accept(Visitor &visitor, const std::shared_ptr<NPC> &defender)
{
    visitor.visit(*this, defender);
}

void Bandit::save(std::ostream &os) const
{
    os << BanditType << " ";
    NPC::save(os);
}

void Bandit::print() const
{
    std::cout << "Bandit: " << name << " at (" << x << ", " << y << ")" << std::endl;
}