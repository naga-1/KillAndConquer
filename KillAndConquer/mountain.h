#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#include "case.h"

class Mountain : public Case
{
private :
        static vector<int> db;
        static vector<int> mb;

public:
    Mountain(int x, int y, int nbPlayer, Building* building, Unit* unit);
};

#endif // MOUNTAIN_H
