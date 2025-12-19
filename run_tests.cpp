#include <iostream>
#include <cassert>
#include <cmath>
#include <mutex>
#include <atomic>
#include <shared_mutex>
#include "npc.h"
#include "factory.h"

void runAllTests() {
    std::cout << "=== Running Lab07 Tests ===\n\n";
    
    // Тест 1: Создание NPC
    std::cout << "Test 1: Creating NPCs... ";
    {
        Orc orc("TestOrc", 10, 20);
        assert(orc.getName() == "TestOrc");
        assert(orc.getType() == NPCType::ORC);
        assert(orc.getX() == 10);
        assert(orc.getY() == 20);
        assert(orc.isAlive());
        assert(orc.getMoveDistance() == 20);
        assert(orc.getKillDistance() == 10);
    }
    std::cout << "PASSED ✓\n";
    
    // Тест 2: Движение
    std::cout << "Test 2: NPC movement... ";
    {
        Knight knight("TestKnight", 50, 50);
        knight.move(100, 100);
        
        // Проверяем что остался в пределах карты
        assert(knight.getX() >= 0 && knight.getX() < 100);
        assert(knight.getY() >= 0 && knight.getY() < 100);
    }
    std::cout << "PASSED ✓\n";
    
    // Тест 3: Расстояние
    std::cout << "Test 3: Distance calculation... ";
    {
        Dragon d1("D1", 0, 0);
        Dragon d2("D2", 3, 4);
        
        double dist = d1.distanceTo(d2);
        assert(std::abs(dist - 5.0) < 0.0001);
    }
    std::cout << "PASSED ✓\n";
    
    // Тест 4: Дистанция убийства
    std::cout << "Test 4: Kill distance check... ";
    {
        Elf elf("Elf", 0, 0);
        Squirrel squirrel("Squirrel", 0, 40);
        
        assert(elf.canKill(squirrel) == true);   // 40 < 50
        assert(squirrel.canKill(elf) == false);  // 40 > 5
    }
    std::cout << "PASSED ✓\n";
    
    // Тест 5: Урон и смерть
    std::cout << "Test 5: Damage and death... ";
    {
        Bear bear("Bear", 0, 0);
        
        assert(bear.isAlive());
        assert(bear.getHealth() == 150);
        
        bear.takeDamage(100);
        assert(bear.getHealth() == 50);
        assert(bear.isAlive());
        
        bear.kill();
        assert(!bear.isAlive());
        assert(bear.getHealth() == 0);
        
        // Мертвый не двигается
        int oldX = bear.getX();
        int oldY = bear.getY();
        bear.move(100, 100);
        assert(bear.getX() == oldX);
        assert(bear.getY() == oldY);
    }
    std::cout << "PASSED ✓\n";
    
    // Тест 6: Все типы из таблицы
    std::cout << "Test 6: All NPC types from table... ";
    {
        // Проверяем параметры из таблицы
        Orc orc("", 0, 0);
        assert(orc.getMoveDistance() == 20 && orc.getKillDistance() == 10);
        
        Squirrel squirrel("", 0, 0);
        assert(squirrel.getMoveDistance() == 5 && squirrel.getKillDistance() == 5);
        
        Dragon dragon("", 0, 0);
        assert(dragon.getMoveDistance() == 50 && dragon.getKillDistance() == 30);
        
        Princess princess("", 0, 0);
        assert(princess.getMoveDistance() == 1 && princess.getKillDistance() == 1);
        
        Werewolf werewolf("", 0, 0);
        assert(werewolf.getMoveDistance() == 40 && werewolf.getKillDistance() == 5);
    }
    std::cout << "PASSED ✓\n";
    
    // Тест 7: Фабрика
    std::cout << "Test 7: NPC Factory... ";
    {
        auto orc = NPCFactory::createNPC(NPCType::ORC, "FactoryOrc", 10, 20);
        assert(orc != nullptr);
        assert(orc->getType() == NPCType::ORC);
        
        auto dragon = NPCFactory::createNPC(NPCType::DRAGON, "FactoryDragon", 30, 40);
        assert(dragon != nullptr);
        assert(dragon->getType() == NPCType::DRAGON);
        
        auto randomNPCs = NPCFactory::createRandomNPCs(5, 100, 100);
        assert(randomNPCs.size() == 5);
        for (const auto& npc : randomNPCs) {
            assert(npc != nullptr);
            assert(npc->getX() >= 0 && npc->getX() < 100);
            assert(npc->getY() >= 0 && npc->getY() < 100);
        }
    }
    std::cout << "PASSED ✓\n";
    
    // Тест 8: Многопоточность (базовая проверка)
    std::cout << "Test 8: Thread safety structures... ";
    {
        // Просто проверяем что классы компилируются
        std::mutex m;
        std::lock_guard<std::mutex> lock(m);
        std::atomic<bool> flag{true};
        flag = false;
        
        std::shared_mutex sm;
        std::shared_lock<std::shared_mutex> slock(sm);
    }
    std::cout << "PASSED ✓\n";
    
    std::cout << "\n=== All 8 tests PASSED! ===\n";
}

int main() {
    try {
        runAllTests();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\nTest FAILED: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "\nUnknown test failure\n";
        return 1;
    }
}
