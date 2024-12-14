#include "include/elf.h"
#include "include/visitor.h"

Elf::Elf(int x, int y) : NPC(x, y, "Elf") {}

Elf::Elf(std::istream &is) : NPC(is) {}

void Elf::accept(Visitor &visitor, const std::shared_ptr<NPC> &defender)
{
    visitor.visit(*this, defender);
}

void Elf::save(std::ostream &os) const
{
    os << ElfType << " ";
    NPC::save(os);
}

void Elf::print() const
{
    std::cout << "Elf: " << name << " at (" << x << ", " << y << ")" << std::endl;
}