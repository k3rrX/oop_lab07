#ifndef FACTORY_H
#define FACTORY_H

#include "npc.h"
#include <memory>
#include <random>
#include <vector>
#include <string>

class NPCFactory {
private:
    static std::string generateName(NPCType type, int index) {
        std::string baseName;
        switch(type) {
            case NPCType::ORC: baseName = "Orc"; break;
            case NPCType::SQUIRREL: baseName = "Squirrel"; break;
            case NPCType::DRUID: baseName = "Druid"; break;
            case NPCType::KNIGHT: baseName = "Knight"; break;
            case NPCType::ELF: baseName = "Elf"; break;
            case NPCType::DRAGON: baseName = "Dragon"; break;
            case NPCType::BEAR: baseName = "Bear"; break;
            case NPCType::BANDIT: baseName = "Bandit"; break;
            case NPCType::WEREWOLF: baseName = "Werewolf"; break;
            case NPCType::PRINCESS: baseName = "Princess"; break;
            case NPCType::TOAD: baseName = "Toad"; break;
            case NPCType::SLAVER: baseName = "Slaver"; break;
            case NPCType::PEGASUS: baseName = "Pegasus"; break;
            case NPCType::BITTERN: baseName = "Bittern"; break;
            case NPCType::DESMAN: baseName = "Desman"; break;
            case NPCType::BULL: baseName = "Bull"; break;
            default: baseName = "Unknown"; break;
        }
        return baseName + "_" + std::to_string(index);
    }
    
public:
    static std::unique_ptr<NPC> createNPC(NPCType type, 
                                          const std::string& name, 
                                          int x, int y) {
        switch(type) {
            case NPCType::ORC: return std::make_unique<Orc>(name, x, y);
            case NPCType::SQUIRREL: return std::make_unique<Squirrel>(name, x, y);
            case NPCType::DRUID: return std::make_unique<Druid>(name, x, y);
            case NPCType::KNIGHT: return std::make_unique<Knight>(name, x, y);
            case NPCType::ELF: return std::make_unique<Elf>(name, x, y);
            case NPCType::DRAGON: return std::make_unique<Dragon>(name, x, y);
            case NPCType::BEAR: return std::make_unique<Bear>(name, x, y);
            case NPCType::BANDIT: return std::make_unique<Bandit>(name, x, y);
            case NPCType::WEREWOLF: return std::make_unique<Werewolf>(name, x, y);
            case NPCType::PRINCESS: return std::make_unique<Princess>(name, x, y);
            case NPCType::TOAD: return std::make_unique<Toad>(name, x, y);
            case NPCType::SLAVER: return std::make_unique<Slaver>(name, x, y);
            case NPCType::PEGASUS: return std::make_unique<Pegasus>(name, x, y);
            case NPCType::BITTERN: return std::make_unique<Bittern>(name, x, y);
            case NPCType::DESMAN: return std::make_unique<Desman>(name, x, y);
            case NPCType::BULL: return std::make_unique<Bull>(name, x, y);
            default: return nullptr;
        }
    }
    
    static std::vector<std::unique_ptr<NPC>> createRandomNPCs(int count, 
                                                              int maxX, 
                                                              int maxY) {
        std::vector<std::unique_ptr<NPC>> npcs;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> typeDist(0, 15);
        std::uniform_int_distribution<> xDist(0, maxX - 1);
        std::uniform_int_distribution<> yDist(0, maxY - 1);
        
        std::vector<NPCType> allTypes = {
            NPCType::ORC, NPCType::SQUIRREL, NPCType::DRUID,
            NPCType::KNIGHT, NPCType::ELF, NPCType::DRAGON,
            NPCType::BEAR, NPCType::BANDIT, NPCType::WEREWOLF,
            NPCType::PRINCESS, NPCType::TOAD, NPCType::SLAVER,
            NPCType::PEGASUS, NPCType::BITTERN, NPCType::DESMAN,
            NPCType::BULL
        };
        
        for (int i = 0; i < count; ++i) {
            NPCType type = allTypes[typeDist(gen)];
            std::string name = generateName(type, i + 1);
            int x = xDist(gen);
            int y = yDist(gen);
            
            npcs.push_back(createNPC(type, name, x, y));
        }
        
        return npcs;
    }
};

#endif