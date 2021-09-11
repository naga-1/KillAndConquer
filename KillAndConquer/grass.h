#ifndef GRASS_H
#define GRASS_H
#include "case.h"

class Grass : public Case
{
private :
        static vector<int> db;
        static vector<int> mb;

public:
    Grass(int x, int y, int nbPlayer, Building* building, Unit* unit);
};

#endif // GRASS_H
