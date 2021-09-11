#include "knight.h"

/*!
 * \brief Knight::Knight, constructor of a knight, its life is set to 10 hp, damage to 5, damage radius to 1 and moving radius to 2
 * \param player, the player who own the knight
 * \param x, x position in the map (logicMap)
 * \param y, y position in the map (logicMap)
 */

Knight::Knight(int player, int x, int y) : Unit(3, player, x, y, 10, 5, 1, 2)
{

}

/*!
 * \brief Knight::Knight
 */
Knight::Knight() : Unit()
{
    this->movingRadius = 2;
}
