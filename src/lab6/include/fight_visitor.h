#pragma once
#include <memory>

struct Bear;
struct Elf;
struct Bandit;

struct FightVisitor {
    virtual void visit(std::shared_ptr<Bear> bear) = 0;
    virtual void visit(std::shared_ptr<Elf> elf) = 0;
    virtual void visit(std::shared_ptr<Bandit> bandit) = 0;
};