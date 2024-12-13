#pragma once
#include "npc.h"

struct Bear : public NPC
{
    Bear(int x, int y);
    Bear(std::istream &is);

    void print() override;

    bool is_bear() const override;

    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Elf> other) override;
    bool fight(std::shared_ptr<Bandit> other) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Bear &Bear);
};