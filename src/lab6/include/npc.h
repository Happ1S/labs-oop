#ifndef NPC_H
#define NPC_H

#include <string>
#include <memory>
#include <iostream>
#include <set>
#include <vector>


class Bear;
class Elf;
class Bandit;
class Visitor;


enum NpcType
{
    BearType = 1,
    ElfType,
    BanditType
};


class IFightObserver
{
public:
    virtual void on_fight(const std::shared_ptr<class NPC> attacker, const std::shared_ptr<class NPC> defender, bool win) = 0;
};


class NPC : public std::enable_shared_from_this<NPC>
{
public:
    int x, y;
    std::string name;
    bool alive;
    std::vector<std::shared_ptr<IFightObserver>> observers;

public:

    NPC(int x, int y, const std::string &name);
    NPC(std::istream &is);
    virtual ~NPC() = default;
    virtual NpcType getType() const = 0;
    
    virtual void accept(Visitor &visitor, const std::shared_ptr<NPC> &defender) = 0;
    virtual void save(std::ostream &os) const;
    virtual void print() const;

    bool is_close(const std::shared_ptr<NPC> &other, size_t distance) const;
    void subscribe(const std::shared_ptr<IFightObserver> &observer);
    void notify(const std::shared_ptr<NPC> &defender, bool win);
    bool is_alive() const { return alive; }
};

using set_t = std::set<std::shared_ptr<NPC>>;

#endif 