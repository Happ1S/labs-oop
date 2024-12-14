#ifndef BANDIT_H
#define BANDIT_H

#include "npc.h"

class Bandit : public NPC
{
public:
    Bandit(int x, int y);
    Bandit(std::istream &is);
    NpcType getType() const override { return BanditType; }

    void accept(Visitor &visitor, const std::shared_ptr<NPC> &defender) override;
    void save(std::ostream &os) const override;
    void print() const override;
};

#endif 