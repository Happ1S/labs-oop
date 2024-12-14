#ifndef BEAR_H
#define BEAR_H

#include "npc.h"

class Bear : public NPC
{
public:
    Bear(int x, int y);
    Bear(std::istream &is);

    NpcType getType() const override { return BearType; }
    void accept(Visitor &visitor, const std::shared_ptr<NPC> &defender) override;
    void save(std::ostream &os) const override;
    void print() const override;
};

#endif 