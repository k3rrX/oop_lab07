#include "game.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Game::Game() {
    // Создаем 50 NPC в случайных локациях
    auto newNPCs = NPCFactory::createRandomNPCs(50, mapX, mapY);
    
    std::unique_lock<std::shared_mutex> lock(npcsMutex);
    for (auto& npc : newNPCs) {
        npcs.push_back(std::move(npc));
    }
    
    std::lock_guard<std::mutex> coutLock(coutMutex);
    std::cout << "Created 50 NPCs on " << mapX << "x" << mapY << " map\n";
}

Game::~Game() {
    stop();
}

void Game::start() {
    running = true;
    
    // Запускаем потоки
    movementThread = std::thread(&Game::movementWorker, this);
    battleThread = std::thread(&Game::battleWorker, this);
    displayThread = std::thread(&Game::displayWorker, this);
    
    {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Game started! Running for 30 seconds...\n";
    }
    
    // Ждем 30 секунд
    std::this_thread::sleep_for(std::chrono::seconds(30));
    
    stop();
    printSurvivors();
}

void Game::stop() {
    running = false;
    battleCV.notify_all();
    
    if (movementThread.joinable()) movementThread.join();
    if (battleThread.joinable()) battleThread.join();
    if (displayThread.joinable()) displayThread.join();
}

void Game::movementWorker() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        std::shared_lock<std::shared_mutex> readLock(npcsMutex);
        std::vector<std::shared_ptr<NPC>> currentNPCs = npcs;
        readLock.unlock();
        
        // Перемещаем живых NPC
        for (auto& npc : currentNPCs) {
            if (npc->isAlive()) {
                npc->move(mapX, mapY);
            }
        }
        
        // Проверяем дистанции для боя
        std::unique_lock<std::shared_mutex> writeLock(npcsMutex);
        for (size_t i = 0; i < npcs.size() && running; ++i) {
            if (!npcs[i]->isAlive()) continue;
            
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (!npcs[j]->isAlive()) continue;
                
                if (npcs[i]->canKill(*npcs[j])) {
                    BattleTask task{npcs[i], npcs[j]};
                    
                    std::lock_guard<std::mutex> queueLock(battleQueueMutex);
                    battleQueue.push(task);
                    battleCV.notify_one();
                }
            }
        }
    }
}

void Game::battleWorker() {
    while (running) {
        BattleTask task;
        
        {
            std::unique_lock<std::mutex> lock(battleQueueMutex);
            battleCV.wait(lock, [this]() { 
                return !battleQueue.empty() || !running; 
            });
            
            if (!running && battleQueue.empty()) break;
            
            if (!battleQueue.empty()) {
                task = battleQueue.front();
                battleQueue.pop();
            }
        }
        
        if (task.attacker && task.defender) {
            // Проверяем, что NPC еще живы
            if (!task.attacker->isAlive() || !task.defender->isAlive()) {
                continue;
            }
            
            // Кидаем кубики
            bool attackerWins = rollDice();
            
            {
                std::lock_guard<std::mutex> coutLock(coutMutex);
                std::cout << "BATTLE: " << task.attacker->getName() 
                          << " vs " << task.defender->getName();
                std::cout << " -> " << (attackerWins ? task.attacker->getName() 
                                                    : task.defender->getName())
                          << " wins!\n";
            }
            
            if (attackerWins) {
                task.defender->kill();
            } else {
                task.attacker->kill();
            }
        }
    }
}

void Game::displayWorker() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        printMap();
    }
}

void Game::printMap() const {
    std::lock_guard<std::mutex> coutLock(coutMutex);
    
    std::cout << "\n=== MAP " << mapX << "x" << mapY << " ===\n";
    
    // Простой вывод статистики вместо графической карты
    std::shared_lock<std::shared_mutex> lock(npcsMutex);
    
    int aliveCount = 0;
    int deadCount = 0;
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            aliveCount++;
        } else {
            deadCount++;
        }
    }
    
    std::cout << "Alive NPCs: " << aliveCount << "\n";
    std::cout << "Dead NPCs: " << deadCount << "\n";
    
    // Покажем первых 5 живых NPC
    int count = 0;
    std::cout << "Some NPCs positions:\n";
    for (const auto& npc : npcs) {
        if (npc->isAlive() && count < 5) {
            std::cout << "  " << npc->getName() << " at [" 
                      << npc->getX() << "," << npc->getY() << "]\n";
            count++;
        }
    }
    
    std::cout << "---\n";
}

void Game::printSurvivors() const {
    std::lock_guard<std::mutex> coutLock(coutMutex);
    
    std::cout << "\n=== SURVIVORS ===\n";
    
    std::shared_lock<std::shared_mutex> lock(npcsMutex);
    
    int count = 0;
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            std::cout << ++count << ". " << npc->toString() << "\n";
        }
    }
    
    if (count == 0) {
        std::cout << "No survivors!\n";
    } else {
        std::cout << "Total survivors: " << count << "\n";
    }
}
