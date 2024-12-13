#pragma once
#include "npc.h"
#include "fight_visitor.h"

struct Bandit : public NPC
{
    Bandit(int x, int y);
    Bandit(std::istream &is);

    void print() override;

    void accept(FightVisitor &visitor) override;

    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Elf> other) override;
    bool fight(std::shared_ptr<Bandit> other) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Bandit &Bandit);
};

