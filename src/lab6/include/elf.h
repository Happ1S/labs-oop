#pragma once
#include "npc.h"
#include "fight_visitor.h"

struct Elf : public NPC {
    Elf(int x, int y);
    Elf(std::istream &is);

    void print() override;
    void accept(FightVisitor &visitor) override;
    bool fight(std::shared_ptr<NPC> other) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Elf &bear);
};