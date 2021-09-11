#ifndef CITY_H
#define CITY_H
#include "building.h"


class City : public Building
{

protected:
    string name;
    bool hasCreateUnit;
    bool isTaken;
    int defenceBonus;
public:
    City(int, string);

    string getName();
    bool getHasCreateUnit();
    bool getIsTaken();
    int getDefenceBonus();

    void setHasCreateUnit(bool);
    void setIsTaken(bool istake);
    void setName(string); //usefull ?
    virtual ~City();
};

#endif // CITY_H
