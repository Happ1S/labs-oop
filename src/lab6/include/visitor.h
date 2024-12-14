#ifndef VISITOR_H
#define VISITOR_H

#include <memory>
#include "npc.h"

class Bear;
class Elf;
class Bandit;

class Visitor
{
private:
    bool success;

public:
    Visitor();

    void visit(Bear &attacker, const std::shared_ptr<NPC> &defender);
    void visit(Elf &attacker, const std::shared_ptr<NPC> &defender);
    void visit(Bandit &attacker, const std::shared_ptr<NPC> &defender);

    bool is_success() const;
};

#endif 