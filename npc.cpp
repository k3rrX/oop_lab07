#include "npc.h"

std::string NPC::getTypeString() const {
    switch(type) {
        case NPCType::ORC: return "Orc";
        case NPCType::SQUIRREL: return "Squirrel";
        case NPCType::DRUID: return "Druid";
        case NPCType::KNIGHT: return "Knight";
        case NPCType::ELF: return "Elf";
        case NPCType::DRAGON: return "Dragon";
        case NPCType::BEAR: return "Bear";
        case NPCType::BANDIT: return "Bandit";
        case NPCType::WEREWOLF: return "Werewolf";
        case NPCType::PRINCESS: return "Princess";
        case NPCType::TOAD: return "Toad";
        case NPCType::SLAVER: return "Slaver";
        case NPCType::PEGASUS: return "Pegasus";
        case NPCType::BITTERN: return "Bittern";
        case NPCType::DESMAN: return "Desman";
        case NPCType::BULL: return "Bull";
        default: return "Unknown";
    }
}