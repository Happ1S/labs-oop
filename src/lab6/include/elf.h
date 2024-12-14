#pragma once
#include "npc.h"
#include "fight_visitor.h"
#include "bear.h"    // Include Bear
#include "bandit.h"  // Include Bandit

struct Elf : public NPC {
    Elf(int x, int y);
    Elf(std::istream &is);

    void print() override;
    
    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Elf> other) override;
    bool fight(std::shared_ptr<Bandit> other) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Elf &elf);
};