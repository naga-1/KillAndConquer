#ifndef UNIT_H
#define UNIT_H
#include "entity.h"

class Unit : public Entity{

protected:
    int id;
    int maxHp;
    int hp;
    int damage;
    int NumberOfKills;
    int damageRadius;
    int movingRadius;

    bool hasMoved;
    bool hasAttacked;
    bool isDead;

    void HealUnitOrNot();
    void setHp(int);
    void setIsDead();

public:
    Unit(int id, int player, int x, int y, int hp, int damage, int damageRadius, int movingRadius);
    Unit();

    int getId();
    int getHp();
    int getMaxHp();
    int getdamage();
    int getNumberOfKills();
    int getDamageRadius();
    int getMovingRadius();
    bool getHasMoved();
    bool getHasAttacked();
    bool isUnitDead();

    void moveTo(int x, int y);
    void AddOneKill();
    void setHasMoved();
    void setHasAttacked();
    void resetHasMoved();
    void resetHasAttacked();

    void takeDamage(int);
    bool operator==(Unit*);
    void operator+(Unit*);
};

#endif // UNIT_H
