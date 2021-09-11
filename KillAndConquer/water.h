#ifndef WATER_H
#define WATER_H
#include "case.h"

class Water : public Case
{
private :
        static vector<int> db;
        static vector<int> mb;

public:
    Water(int x, int y, int nbPlayer, Building* building, Unit* unit);
};

#endif // WATER_H
