#include "include/bear.h"
#include "include/visitor.h"

Bear::Bear(int x, int y) : NPC(x, y, "Bear") {}

Bear::Bear(std::istream &is) : NPC(is) {}

void Bear::accept(Visitor &visitor, const std::shared_ptr<NPC> &defender)
{
    visitor.visit(*this, defender);
}

void Bear::save(std::ostream &os) const
{
    os << BearType << " ";
    NPC::save(os);
}

void Bear::print() const
{
    std::cout << "Bear: " << name << " at (" << x << ", " << y << ")" << std::endl;
}