#include "include/npc.h"

NPC::NPC(int x, int y, const std::string &name) : x(x), y(y), name(name) {}

NPC::NPC(std::istream &is)
{
    is >> x >> y >> name;
}

void NPC::save(std::ostream &os) const
{
    os << x << " " << y << " " << name << std::endl;
}

void NPC::print() const
{
    std::cout << "NPC: " << name << " at (" << x << ", " << y << ")" << std::endl;
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) const
{
    int dx = x - other->x;
    int dy = y - other->y;
    return (dx * dx + dy * dy) <= (distance * distance);
}

void NPC::subscribe(const std::shared_ptr<IFightObserver> &observer)
{
    observers.push_back(observer);
}

void NPC::notify(const std::shared_ptr<NPC> &defender, bool win)
{
    for (auto &observer : observers)
    {
        observer->on_fight(shared_from_this(), defender, win);
    }
}