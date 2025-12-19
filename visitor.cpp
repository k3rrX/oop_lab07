#include "visitor.h"
#include "observer.h"

// Реализация методов ConcreteBattleVisitor
void ConcreteBattleVisitor::visit(Dragon& dragon, Knight& knight) {
    if (observer) {
        observer->update("Дракон '" + dragon.getName() + 
                        "' атакует рыцаря '" + knight.getName() + "'");
    }
    dragon.attack(knight);
    if (knight.isAlive()) {
        if (observer) {
            observer->update("Рыцарь '" + knight.getName() + 
                            "' контратакует дракона '" + dragon.getName() + "'");
        }
        knight.attack(dragon);
    }
}

void ConcreteBattleVisitor::visit(Dragon& dragon1, Dragon& dragon2) {
    if (observer) {
        observer->update("Дракон '" + dragon1.getName() + 
                        "' сражается с драконом '" + dragon2.getName() + "'");
    }
    dragon1.attack(dragon2);
    dragon2.attack(dragon1);
}

void ConcreteBattleVisitor::visit(Knight& knight1, Knight& knight2) {
    if (observer) {
        observer->update("Рыцарь '" + knight1.getName() + 
                        "' сражается с рыцарем '" + knight2.getName() + "'");
    }
    knight1.attack(knight2);
    knight2.attack(knight1);
}

void ConcreteBattleVisitor::visit(Wanderer& wanderer1, Wanderer& wanderer2) {
    if (observer) {
        observer->update("Странник '" + wanderer1.getName() + 
                        "' сражается со странником '" + wanderer2.getName() + "'");
    }
    wanderer1.attack(wanderer2);
    wanderer2.attack(wanderer1);
}

void ConcreteBattleVisitor::visit(Dragon& dragon, Wanderer& wanderer) {
    if (observer) {
        observer->update("Дракон '" + dragon.getName() + 
                        "' атакует странника '" + wanderer.getName() + "'");
    }
    dragon.attack(wanderer);
    if (wanderer.isAlive()) {
        if (observer) {
            observer->update("Странник '" + wanderer.getName() + 
                            "' пытается защититься от дракона '" + dragon.getName() + "'");
        }
        wanderer.attack(dragon);
    }
}

void ConcreteBattleVisitor::visit(Knight& knight, Wanderer& wanderer) {
    if (observer) {
        observer->update("⚔️ Рыцарь '" + knight.getName() + 
                        "' атакует странника '" + wanderer.getName() + "'");
    }
    knight.attack(wanderer);
    if (wanderer.isAlive()) {
        if (observer) {
            observer->update("🏹 Странник '" + wanderer.getName() + 
                            "' защищается от рыцаря '" + knight.getName() + "'");
        }
        wanderer.attack(knight);
    }
}