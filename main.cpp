#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <random>
#include <chrono>
#include <map>
#include <map>
#include "src/lab6/include/npc.h"
#include "src/lab6/include/elf.h"
#include "src/lab6/include/bandit.h"
#include "src/lab6/include/bear.h"
#include "src/lab6/include/visitor.h"

constexpr int MAP_SIZE = 100;
constexpr int NUM_NPCS = 50;
constexpr int GAME_DURATION = 30;

std::vector<std::shared_ptr<NPC>> npcs;
std::shared_mutex npc_mutex;
std::mutex cout_mutex;
bool game_running = true;

std::map<NpcType, std::pair<int, int>> kill_table = {
    {BearType, {5, 10}},
    {ElfType, {10, 50}},
    {BanditType, {10, 10}}
};

class TextObserver : public IFightObserver {
public:
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::lock_guard<std::mutex> lck(cout_mutex);
            std::cout << attacker->name << " defeated " << defender->name << "!\n";
        }
    }
};

std::shared_ptr<NPC> factory(NpcType type, int x, int y) {
    std::shared_ptr<NPC> result;
    switch (type) {
    case BearType:
        result = std::make_shared<Bear>(x, y);
        break;
    case ElfType:
        result = std::make_shared<Elf>(x, y);
        break;
    case BanditType:
        result = std::make_shared<Bandit>(x, y);
        break;
    default:
        break;
    }
    if (result) {
        result->subscribe(std::make_shared<TextObserver>());
    }
    return result;
}

void move_npcs() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-1, 1);
    while (game_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::unique_lock lock(npc_mutex);
        for (auto &npc : npcs) {
            int move_distance = kill_table[npc->getType()].first;
            if (npc->getType() != BearType) { 
                npc->x = std::clamp(npc->x + distribution(generator) * move_distance, 0, MAP_SIZE - 1);
                npc->y = std::clamp(npc->y + distribution(generator) * move_distance, 0, MAP_SIZE - 1);
                npc->x = std::clamp(npc->x + distribution(generator) * move_distance, 0, MAP_SIZE - 1);
                npc->y = std::clamp(npc->y + distribution(generator) * move_distance, 0, MAP_SIZE - 1);
            }
        }
    }
}

void combat_npcs() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> dice_roll(1, 6);
    Visitor visitor;
    while (game_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::unique_lock lock(npc_mutex);
        for (size_t i = 0; i < npcs.size(); ++i) {
            int kill_distance = kill_table[npcs[i]->getType()].second;
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (npcs[i]->is_close(npcs[j], kill_distance)) {
                    int attack = dice_roll(generator);
                    int defense = dice_roll(generator);
                    if (attack > defense) {
                        npcs[i]->accept(visitor, npcs[j]);
                        std::lock_guard cout_lock(cout_mutex);
                        std::cout << npcs[i]->name << " attacked " << npcs[j]->name << " and won!\n";
                    } else {
                        std::lock_guard cout_lock(cout_mutex);
                        std::cout << npcs[i]->name << " attacked " << npcs[j]->name << " and lost.\n";
                    }
                }
            }
        }
    }
}

void print_map() {
    while (game_running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::shared_lock lock(npc_mutex);
        std::lock_guard cout_lock(cout_mutex);
        std::cout << "Map state:\n";
        for (const auto &npc : npcs) {
            if (npc->getType() != BearType) { 
                std::cout << npc->name << " at (" << npc->x << ", " << npc->y << ")\n";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, MAP_SIZE - 1);
    std::uniform_int_distribution<int> npc_type_distribution(1, 3); 

    for (int i = 0; i < NUM_NPCS; ++i) {
        int x = distribution(generator);
        int y = distribution(generator);
        int npc_type = npc_type_distribution(generator);
        npcs.push_back(factory(NpcType(npc_type), x, y));
        npcs.push_back(factory(NpcType(npc_type), x, y));
    }

    std::thread move_thread(move_npcs);
    std::thread combat_thread(combat_npcs);
    std::thread print_thread(print_map);

    std::this_thread::sleep_for(std::chrono::seconds(GAME_DURATION));
    game_running = false;

    move_thread.join();
    combat_thread.join();
    print_thread.join();

    std::cout << "Survivors:\n";
    for (const auto &npc : npcs) {
        if (npc->getType() != BearType) { 
            std::cout << npc->name << " at (" << npc->x << ", " << npc->y << ")\n";
        }
    }

    return 0;
}