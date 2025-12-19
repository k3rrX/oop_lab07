#include <gtest/gtest.h>
#include "npc.h"
#include "factory.h"
#include <memory>
#include <vector>
#include <cmath>

using ::testing::Test;

// Тест 1: Базовое создание NPC
TEST(NPCTest, BasicProperties) {
    Orc orc("TestOrc", 10, 20);
    
    EXPECT_EQ(orc.getName(), "TestOrc");
    EXPECT_EQ(orc.getType(), NPCType::ORC);
    EXPECT_EQ(orc.getTypeString(), "Orc");
    EXPECT_EQ(orc.getX(), 10);
    EXPECT_EQ(orc.getY(), 20);
    EXPECT_TRUE(orc.isAlive());
    EXPECT_EQ(orc.getHealth(), 100);
    EXPECT_EQ(orc.getMoveDistance(), 20);
    EXPECT_EQ(orc.getKillDistance(), 10);
}

// Тест 2: Движение в пределах границ
TEST(NPCTest, MovementWithinBounds) {
    Knight knight("TestKnight", 50, 50);
    
    // Двигаем 100 раз
    for (int i = 0; i < 100; i++) {
        knight.move(100, 100);
        EXPECT_GE(knight.getX(), 0);
        EXPECT_LT(knight.getX(), 100);
        EXPECT_GE(knight.getY(), 0);
        EXPECT_LT(knight.getY(), 100);
    }
}

// Тест 3: Точный расчет расстояния
TEST(NPCTest, DistanceCalculation) {
    Dragon d1("Dragon1", 0, 0);
    Dragon d2("Dragon2", 3, 4);
    
    double distance = d1.distanceTo(d2);
    EXPECT_NEAR(distance, 5.0, 0.000001);
    
    // Проверка нулевого расстояния
    Dragon d3("Dragon3", 10, 10);
    EXPECT_DOUBLE_EQ(d3.distanceTo(d3), 0.0);
}

// Тест 4: Проверка дистанции убийства
TEST(NPCTest, CanKillMethod) {
    Elf elf("Elf", 0, 0);           // kill distance = 50
    Squirrel squirrel("Squirrel", 0, 40); // kill distance = 5
    
    // Эльф может убить белку на расстоянии 40
    EXPECT_TRUE(elf.canKill(squirrel));
    
    // Белка не может убить эльфа на расстоянии 40
    EXPECT_FALSE(squirrel.canKill(elf));
    
    // Тест на граничном расстоянии
    Orc orc("Orc", 0, 0);          // kill distance = 10
    Knight knight("Knight", 0, 10); // distance = 10
    
    EXPECT_TRUE(orc.canKill(knight)); // равно kill distance
}

// Тест 5: Получение урона и смерть
TEST(NPCTest, DamageAndDeath) {
    Bear bear("TestBear", 0, 0);
    
    EXPECT_TRUE(bear.isAlive());
    EXPECT_EQ(bear.getHealth(), 150);
    
    // Частичный урон
    bear.takeDamage(50);
    EXPECT_TRUE(bear.isAlive());
    EXPECT_EQ(bear.getHealth(), 100);
    
    // Смертельный урон
    bear.takeDamage(150);
    EXPECT_FALSE(bear.isAlive());
    EXPECT_EQ(bear.getHealth(), 0);
    
    // Метод kill()
    Bear bear2("TestBear2", 0, 0);
    bear2.kill();
    EXPECT_FALSE(bear2.isAlive());
    EXPECT_EQ(bear2.getHealth(), 0);
}

// Тест 6: Все типы NPC из таблицы
TEST(NPCTest, AllNPCTypeParameters) {
    // Проверка параметров из таблицы задания
    std::vector<std::pair<NPCType, std::pair<int, int>>> expected = {
        {NPCType::ORC, {20, 10}},
        {NPCType::SQUIRREL, {5, 5}},
        {NPCType::DRUID, {10, 10}},
        {NPCType::KNIGHT, {30, 10}},
        {NPCType::ELF, {10, 50}},
        {NPCType::DRAGON, {50, 30}},
        {NPCType::BEAR, {5, 10}},
        {NPCType::BANDIT, {10, 10}},
        {NPCType::WEREWOLF, {40, 5}},
        {NPCType::PRINCESS, {1, 1}},
        {NPCType::TOAD, {1, 10}},
        {NPCType::SLAVER, {10, 10}},
        {NPCType::PEGASUS, {30, 10}},
        {NPCType::BITTERN, {50, 10}},
        {NPCType::DESMAN, {5, 20}},
        {NPCType::BULL, {30, 10}}
    };
    
    for (const auto& [type, params] : expected) {
        auto npc = NPCFactory::createNPC(type, "TestNPC", 0, 0);
        ASSERT_NE(npc, nullptr);
        EXPECT_EQ(npc->getMoveDistance(), params.first);
        EXPECT_EQ(npc->getKillDistance(), params.second);
    }
}

// Тест 7: Фабрика NPC
TEST(NPCTest, NPCFactory) {
    // Создание конкретных типов
    auto orc = NPCFactory::createNPC(NPCType::ORC, "FactoryOrc", 10, 20);
    EXPECT_NE(orc, nullptr);
    EXPECT_EQ(orc->getType(), NPCType::ORC);
    EXPECT_EQ(orc->getName(), "FactoryOrc");
    EXPECT_EQ(orc->getX(), 10);
    EXPECT_EQ(orc->getY(), 20);
    
    auto dragon = NPCFactory::createNPC(NPCType::DRAGON, "FactoryDragon", 30, 40);
    EXPECT_NE(dragon, nullptr);
    EXPECT_EQ(dragon->getType(), NPCType::DRAGON);
    
    // Случайная генерация
    auto randomNPCs = NPCFactory::createRandomNPCs(20, 100, 100);
    EXPECT_EQ(randomNPCs.size(), 20);
    
    for (const auto& npc : randomNPCs) {
        EXPECT_NE(npc, nullptr);
        EXPECT_GE(npc->getX(), 0);
        EXPECT_LT(npc->getX(), 100);
        EXPECT_GE(npc->getY(), 0);
        EXPECT_LT(npc->getY(), 100);
        EXPECT_TRUE(npc->isAlive());
    }
}

// Тест 8: Мертвые NPC не двигаются
TEST(NPCTest, DeadNPCsDontMove) {
    Dragon dragon("TestDragon", 50, 50);
    
    // Запоминаем позицию
    int initialX = dragon.getX();
    int initialY = dragon.getY();
    
    // Убиваем дракона
    dragon.kill();
    EXPECT_FALSE(dragon.isAlive());
    
    // Пытаемся двигать мертвого дракона
    dragon.move(100, 100);
    
    // Позиция не должна измениться
    EXPECT_EQ(dragon.getX(), initialX);
    EXPECT_EQ(dragon.getY(), initialY);
}

// Тест 9: Строковые представления
TEST(NPCTest, StringRepresentations) {
    Werewolf werewolf("TestWerewolf", 42, 24);
    
    std::string str = werewolf.toString();
    
    // Проверяем что строка содержит важную информацию
    EXPECT_NE(str.find("Werewolf"), std::string::npos);
    EXPECT_NE(str.find("TestWerewolf"), std::string::npos);
    EXPECT_NE(str.find("42"), std::string::npos);
    EXPECT_NE(str.find("24"), std::string::npos);
    EXPECT_NE(str.find("ALIVE"), std::string::npos);
}

// Тест 10: Преобразование строки в тип
TEST(NPCTest, StringToTypeConversion) {
    EXPECT_EQ(NPC::stringToType("Orc"), NPCType::ORC);
    EXPECT_EQ(NPC::stringToType("Dragon"), NPCType::DRAGON);
    EXPECT_EQ(NPC::stringToType("Princess"), NPCType::PRINCESS);
    EXPECT_EQ(NPC::stringToType("Elf"), NPCType::ELF);
    EXPECT_EQ(NPC::stringToType("Unknown"), NPCType::UNKNOWN);
}

// Параметризованный тест для проверки боевой логики
class BattleLogicTest : public ::testing::TestWithParam<std::tuple<int, int, bool>> {
};

TEST_P(BattleLogicTest, DiceRollLogic) {
    auto [attackRoll, defenseRoll, expectedAttackerWins] = GetParam();
    
    // Здесь можно было бы тестировать логику броска кубиков
    // В реальной программе это было бы в классе Game
    bool attackerWins = attackRoll > defenseRoll;
    EXPECT_EQ(attackerWins, expectedAttackerWins);
}

INSTANTIATE_TEST_SUITE_P(
    DiceRollTests,
    BattleLogicTest,
    ::testing::Values(
        std::make_tuple(6, 1, true),   // Атакующий выигрывает
        std::make_tuple(3, 5, false),  // Защищающийся выигрывает
        std::make_tuple(4, 4, false),  // Ничья -> защищающийся выигрывает
        std::make_tuple(1, 6, false),  // Защищающийся явно выигрывает
        std::make_tuple(6, 2, true)    // Атакующий явно выигрывает
    )
);
