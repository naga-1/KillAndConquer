#ifndef MOUNTEDARCHER_H
#define MOUNTEDARCHER_H
#include "archer.h"
#include "knight.h"

class mountedArcher : public Archer, public Knight
{
public:
    mountedArcher(int player, int x, int y);
};

#endif // MOUNTEDARCHER_H
