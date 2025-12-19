#ifndef GAME_H
#define GAME_H

#include "npc.h"
#include "factory.h"
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
#include <random>
#include <chrono>

struct BattleTask {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class Game {
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    mutable std::shared_mutex npcsMutex;
    
    std::queue<BattleTask> battleQueue;
    std::mutex battleQueueMutex;
    std::condition_variable battleCV;
    
    std::atomic<bool> running{true};
    std::atomic<int> mapX{100};
    std::atomic<int> mapY{100};
    
    std::thread movementThread;
    std::thread battleThread;
    std::thread displayThread;
    
    mutable std::mutex coutMutex;  // Добавляем mutable
    
    void movementWorker();
    void battleWorker();
    void displayWorker();
    
    bool rollDice() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 6);
        int attack = dis(gen);
        int defense = dis(gen);
        return attack > defense;
    }
    
public:
    Game();
    ~Game();
    
    void start();
    void stop();
    void printMap() const;
    void printSurvivors() const;
};

#endif
