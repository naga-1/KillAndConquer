#include "mountedarcher.h"

/*!
 * \brief mountedArcher::mountedArcher, constructor of a mounted archer, its life is set to 10 hp, damage to 5, damage radius to 2 and moving radius to 2
 * \param player, the player who own the mounted archer
 * \param x, x position in the map (logicMap)
 * \param y, y position in the map (logicMap)
 */
mountedArcher::mountedArcher(int player, int x, int y) : Archer(), Knight()
{
    this->owner = player;
    this->posX = x;
    this->posY = y;

    this->id = 4;
    this->maxHp = 15;
    this->hp = 15;
    this->damage =  Archer().getdamage();
    this->damageRadius = Archer().getDamageRadius();
    this ->movingRadius = Knight().getMovingRadius();

    this->NumberOfKills = 0;
    this->hasMoved = false;
    this->hasAttacked = false;
    this->isDead = false;
}
