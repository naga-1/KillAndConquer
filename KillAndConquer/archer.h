#ifndef ARCHER_H
#define ARCHER_H
#include "unit.h"

class Archer : public virtual Unit
{
public:
    Archer(int player, int x, int y);
    Archer();
};

#endif // ARCHER_H

