#ifndef FOREST_H
#define FOREST_H
#include "case.h"

class Forest : public Case
{
private :
        static vector<int> db;
        static vector<int> mb;

public:
    Forest(int x, int y, int nbPlayer, Building* building, Unit* unit);
};

#endif // FOREST_H
