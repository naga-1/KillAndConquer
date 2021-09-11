#include "infantry.h"

/*!
 * \brief Infantry::Infantry, constructor of an infantry, its life is set to 10 hp, damage to 5, damage radius to 1 and moving radius to 1
 * \param player, the player who own the infantry
 * \param x, x position in the map (logicMap)
 * \param y, y position in the map (logicMap)
 */

Infantry::Infantry(int player, int x, int y) : Unit(1, player, x, y, 10, 5, 1, 1)
{

}
