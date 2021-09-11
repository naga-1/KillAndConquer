#include "archer.h"

/*!
 * \brief Archer::Archer, constructor of an archer, its life is set to 10 hp, damage to 5, damage radius to 2 and moving radius to 1
 * \param player, the player who own the archer
 * \param x, x position in the map (logicMap)
 * \param y, y position in the map (logicMap)
 */
Archer::Archer(int player, int x, int y) : Unit(2, player, x, y, 10, 5, 2, 1)
{

}

/*!
 * \brief Archer::Archer
 */
Archer::Archer() : Unit()
{
    this->damage = 5;
    this->damageRadius = 2;
}


