#ifndef VISITOR_H
#define VISITOR_H

#include "npc.h"
#include <memory>

// Предварительное объявление
class Dragon;
class Knight;
class Wanderer;

// Visitor интерфейс
class BattleVisitor {
public:
    virtual ~BattleVisitor() = default;
    virtual void visit(Dragon& dragon, Knight& knight) = 0;
    virtual void visit(Dragon& dragon1, Dragon& dragon2) = 0;
    virtual void visit(Knight& knight1, Knight& knight2) = 0;
    virtual void visit(Wanderer& wanderer1, Wanderer& wanderer2) = 0;
    virtual void visit(Dragon& dragon, Wanderer& wanderer) = 0;
    virtual void visit(Knight& knight, Wanderer& wanderer) = 0;
};

// Конкретная реализация Visitor
class ConcreteBattleVisitor : public BattleVisitor {
private:
    BattleObserver* observer;
    
public:
    ConcreteBattleVisitor(BattleObserver* obs) : observer(obs) {}
    
    void visit(Dragon& dragon, Knight& knight) override;
    void visit(Dragon& dragon1, Dragon& dragon2) override;
    void visit(Knight& knight1, Knight& knight2) override;
    void visit(Wanderer& wanderer1, Wanderer& wanderer2) override;
    void visit(Dragon& dragon, Wanderer& wanderer) override;
    void visit(Knight& knight, Wanderer& wanderer) override;
};

#endif