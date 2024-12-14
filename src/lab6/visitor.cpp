#include "include/visitor.h"
#include "include/bear.h"
#include "include/elf.h"
#include "include/bandit.h"
#include <cstdlib> 

Visitor::Visitor() : success(false) {}

void Visitor::visit(Elf &attacker, const std::shared_ptr<NPC> &defender)
{
    if (defender->getType() == BanditType)
    {
        
        success = true;
        attacker.notify(defender, true); 
    }
}

void Visitor::visit(Bandit &attacker, const std::shared_ptr<NPC> &defender)
{
    if (defender->getType() == BanditType)
    {
        
        success = (std::rand() % 2 == 0);
        attacker.notify(defender, success);
    }
}

void Visitor::visit(Bear &attacker, const std::shared_ptr<NPC> &defender)
{
    if (defender->getType() == ElfType)
    {
        
        success = true;
        attacker.notify(defender, true); 
    }
}

bool Visitor::is_success() const
{
    return success;
}