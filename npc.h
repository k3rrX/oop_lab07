#ifndef NPC_H
#define NPC_H

#include <string>
#include <cmath>
#include <iostream>
#include <memory>
#include <random>

enum class NPCType {
    ORC,
    SQUIRREL,
    DRUID,
    KNIGHT,
    ELF,
    DRAGON,
    BEAR,
    BANDIT,
    WEREWOLF,
    PRINCESS,
    TOAD,
    SLAVER,
    PEGASUS,
    BITTERN,
    DESMAN,
    BULL,
    UNKNOWN
};

// Базовый класс NPC
class NPC {
protected:
    std::string name;
    NPCType type;
    int x, y;
    int health;
    bool alive;
    int moveDistance;
    int killDistance;
    
public:
    NPC(const std::string& name, NPCType type, int x, int y, 
        int health, int moveDist, int killDist)
        : name(name), type(type), x(x), y(y), 
          health(health), alive(true),
          moveDistance(moveDist), killDistance(killDist) {}
    
    virtual ~NPC() = default;
    
    // Getters
    std::string getName() const { return name; }
    NPCType getType() const { return type; }
    std::string getTypeString() const;
    int getX() const { return x; }
    int getY() const { return y; }
    int getHealth() const { return health; }
    bool isAlive() const { return alive; }
    int getMoveDistance() const { return moveDistance; }
    int getKillDistance() const { return killDistance; }
    
    // Setters
    void setPosition(int newX, int newY) { 
        x = newX; 
        y = newY; 
    }
    
    void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            health = 0;
            alive = false;
        }
    }
    
    void kill() { 
        alive = false; 
        health = 0; 
    }
    
    double distanceTo(const NPC& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
    
    virtual void move(int maxX, int maxY) {
        if (!alive) return;
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(-moveDistance, moveDistance);
        
        int newX = x + dis(gen);
        int newY = y + dis(gen);
        
        // Проверка границ карты
        if (newX < 0) newX = 0;
        if (newX >= maxX) newX = maxX - 1;
        if (newY < 0) newY = 0;
        if (newY >= maxY) newY = maxY - 1;
        
        x = newX;
        y = newY;
    }
    
    bool canKill(const NPC& other) const {
        return distanceTo(other) <= killDistance;
    }
    
    virtual std::string toString() const {
        return getTypeString() + " '" + name + "' [" + 
               std::to_string(x) + "," + std::to_string(y) + 
               "] HP:" + std::to_string(health) + 
               " M:" + std::to_string(moveDistance) +
               " K:" + std::to_string(killDistance) +
               (alive ? " ALIVE" : " DEAD");
    }
    
    static NPCType stringToType(const std::string& typeStr) {
        if (typeStr == "Orc") return NPCType::ORC;
        if (typeStr == "Squirrel") return NPCType::SQUIRREL;
        if (typeStr == "Druid") return NPCType::DRUID;
        if (typeStr == "Knight") return NPCType::KNIGHT;
        if (typeStr == "Elf") return NPCType::ELF;
        if (typeStr == "Dragon") return NPCType::DRAGON;
        if (typeStr == "Bear") return NPCType::BEAR;
        if (typeStr == "Bandit") return NPCType::BANDIT;
        if (typeStr == "Werewolf") return NPCType::WEREWOLF;
        if (typeStr == "Princess") return NPCType::PRINCESS;
        if (typeStr == "Toad") return NPCType::TOAD;
        if (typeStr == "Slaver") return NPCType::SLAVER;
        if (typeStr == "Pegasus") return NPCType::PEGASUS;
        if (typeStr == "Bittern") return NPCType::BITTERN;
        if (typeStr == "Desman") return NPCType::DESMAN;
        if (typeStr == "Bull") return NPCType::BULL;
        return NPCType::UNKNOWN;
    }
};

// Конкретные классы NPC
class Orc : public NPC {
public:
    Orc(const std::string& name, int x, int y)
        : NPC(name, NPCType::ORC, x, y, 100, 20, 10) {}
};

class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, int x, int y)
        : NPC(name, NPCType::SQUIRREL, x, y, 30, 5, 5) {}
};

class Druid : public NPC {
public:
    Druid(const std::string& name, int x, int y)
        : NPC(name, NPCType::DRUID, x, y, 80, 10, 10) {}
};

class Knight : public NPC {
public:
    Knight(const std::string& name, int x, int y)
        : NPC(name, NPCType::KNIGHT, x, y, 120, 30, 10) {}
};

class Elf : public NPC {
public:
    Elf(const std::string& name, int x, int y)
        : NPC(name, NPCType::ELF, x, y, 70, 10, 50) {}
};

class Dragon : public NPC {
public:
    Dragon(const std::string& name, int x, int y)
        : NPC(name, NPCType::DRAGON, x, y, 200, 50, 30) {}
};

class Bear : public NPC {
public:
    Bear(const std::string& name, int x, int y)
        : NPC(name, NPCType::BEAR, x, y, 150, 5, 10) {}
};

class Bandit : public NPC {
public:
    Bandit(const std::string& name, int x, int y)
        : NPC(name, NPCType::BANDIT, x, y, 90, 10, 10) {}
};

class Werewolf : public NPC {
public:
    Werewolf(const std::string& name, int x, int y)
        : NPC(name, NPCType::WEREWOLF, x, y, 110, 40, 5) {}
};

class Princess : public NPC {
public:
    Princess(const std::string& name, int x, int y)
        : NPC(name, NPCType::PRINCESS, x, y, 40, 1, 1) {}
};

class Toad : public NPC {
public:
    Toad(const std::string& name, int x, int y)
        : NPC(name, NPCType::TOAD, x, y, 20, 1, 10) {}
};

class Slaver : public NPC {
public:
    Slaver(const std::string& name, int x, int y)
        : NPC(name, NPCType::SLAVER, x, y, 85, 10, 10) {}
};

class Pegasus : public NPC {
public:
    Pegasus(const std::string& name, int x, int y)
        : NPC(name, NPCType::PEGASUS, x, y, 95, 30, 10) {}
};

class Bittern : public NPC {
public:
    Bittern(const std::string& name, int x, int y)
        : NPC(name, NPCType::BITTERN, x, y, 35, 50, 10) {}
};

class Desman : public NPC {
public:
    Desman(const std::string& name, int x, int y)
        : NPC(name, NPCType::DESMAN, x, y, 25, 5, 20) {}
};

class Bull : public NPC {
public:
    Bull(const std::string& name, int x, int y)
        : NPC(name, NPCType::BULL, x, y, 130, 30, 10) {}
};

#endif