#pragma once
#include "fight_visitor.h"
#include <memory>

class FightVisitorImpl : public FightVisitor {
    std::shared_ptr<NPC> attacker;
    bool &success;

public:
    FightVisitorImpl(std::shared_ptr<NPC> attacker, bool &success) : attacker(attacker), success(success) {}

    void visit(std::shared_ptr<Bear> bear) override {
        success = attacker->fight(bear);
    }

    void visit(std::shared_ptr<Elf> elf) override {
        success = attacker->fight(elf);
    }

    void visit(std::shared_ptr<Bandit> bandit) override {
        success = attacker->fight(bandit);
    }
};