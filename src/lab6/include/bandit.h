#pragma once
#include "npc.h"
#include "fight_visitor.h"
#include "bear.h"    // Include Bear
#include "elf.h"     // Include Elf

struct Bandit : public NPC {
    Bandit(int x, int y);
    Bandit(std::istream &is);

    void print() override;

    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Elf> other) override;
    bool fight(std::shared_ptr<Bandit> other) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Bandit &bandit);
};