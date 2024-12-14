#ifndef ELF_H
#define ELF_H

#include "npc.h"

class Elf : public NPC
{
public:
    Elf(int x, int y);
    Elf(std::istream &is);
    NpcType getType() const override { return ElfType; }

    void accept(Visitor &visitor, const std::shared_ptr<NPC> &defender) override;
    void save(std::ostream &os) const override;
    void print() const override;
};

#endif 