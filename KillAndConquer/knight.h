#ifndef KNIGHT_H
#define KNIGHT_H
#include "unit.h"


class Knight : public virtual Unit
{
public:
    Knight(int player, int x, int y);
    Knight();
};

#endif // INFANTRY_H
