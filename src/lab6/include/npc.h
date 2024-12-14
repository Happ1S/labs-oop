#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <cmath>

struct NPC;
struct FightVisitor;

enum NpcType {
    Unknown = 0,
    BearType = 1,
    ElfType = 2,
    BanditType = 3
};

struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
};

struct NPC : public std::enable_shared_from_this<NPC> {
    NpcType type;
    int x{0};
    int y{0};
    std::vector<std::shared_ptr<IFightObserver>> observers;

    NPC(NpcType t, int _x, int _y);
    NPC(NpcType t, std::istream &is);

    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win);
    virtual bool is_close(const std::shared_ptr<NPC> &other, size_t distance) const;

    virtual void accept(FightVisitor &visitor) = 0;
    virtual bool fight(std::shared_ptr<NPC> other) = 0;
    virtual void print() = 0;

    virtual void save(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
};

std::ostream &operator<<(std::ostream &os, const NPC &npc);