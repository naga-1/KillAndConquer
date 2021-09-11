#include "case.h"

/*!
 * \brief Case::Case, empty constructor of a case
 */
Case::Case()
{

}

/*!
 * \brief Case::getId, returns the id of case to know is type (i.e mountain, water, forest or grass)
 * \return id of the case
 */
int Case::getId()
{
    return this->id;
}

/*!
 * \brief Case::getPosX
 * \return x positon of the case in the map (logicMap)
 */
int Case::getPosX()
{
    return this->posX;
}

/*!
 * \brief Case::getPosY
 * \return y position of the case in the map (logicMap)
 */
int Case::getPosY()
{
    return this->posY;
}

/*!
 * \brief Case::getFogForPlayer, returns true if there is fog in this case for the playerid given
 * \param playerNumber
 * \return a boolean value to know if there is fog on this case for a given playerId
 */
bool Case::getFogForPlayer(int playerNumber)
{
    return this->fogForPlayers.at(playerNumber-1); // verif depassement
}

/*!
 * \brief Case::getMovingBonusUnit, returns a bonus (or malus) that confere the case for the movement for a given unit
 * \param unitId
 * \return moving bonus associated to the given id of a unit
 */
int Case::getMovingBonusUnit(int unitId)
{
    return this->movingBonusUnits.at(unitId - 1); // verif depassement
}

/*!
 * \brief Case::getDamageBonusUnit, returns a bonus (or malus) that confere the case for the damage for a given unit
 * \param unitId
 * \return damage bonus associated to the given id of a unit
 */
int Case::getDamageBonusUnit(int unitId)
{
    return this->damageBonusUnits.at(unitId-1);
}

/*!
 * \brief Case::getUnit
 * \return the unit (ptr) on the case
 */
Unit *Case::getUnit()
{
    return this->unit;
}

/*!
 * \brief Case::setUnit, modify the unit on the case (ptr)
 * \param unit
 */
void Case::setUnit(Unit* unit)
{
    this->unit = unit;
}

/*!
 * \brief Case::getBuilding
 * \return the building (ptr) on the case
 */
Building *Case::getBuilding()
{
    return this->building;
}

/*!
 * \brief Case::removeFogForPlayer, replace the boolean value stating that there is fog for a given player id
 * \param playerNumber
 */
void Case::removeFogForPlayer(int playerNumber)
{
    this->fogForPlayers.at(playerNumber-1) = false;
}

