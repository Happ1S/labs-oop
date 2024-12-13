#pragma once
#include "npc.h"
#include "bear.h"
#include "elf.h"
#include "bandit.h"
#include <memory>

class FightVisitor {
public:
    virtual void visit(std::shared_ptr<Bear> bear) = 0;
    virtual void visit(std::shared_ptr<Elf> elf) = 0;
    virtual void visit(std::shared_ptr<Bandit> bandit) = 0;
};