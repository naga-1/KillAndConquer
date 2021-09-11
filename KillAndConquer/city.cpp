#include "city.h"

/*!
 * \brief City::City, constructor of a city
 * \param player, id of the owner of the city
 * \param name, name of the city
 */
City::City(int player, string name) : Building(player, 5)
{
    this->name=name;
    this->hasCreateUnit=false;
    this->isTaken = false;
    this->defenceBonus=5;
}

/*!
 * \brief City::getName
 * \return name of the city
 */
string City::getName()
{
    return this->name;
}

/*!
 * \brief City::getHasCreateUnit
 * \return a boolean value to know if the city has create a unit
 */
bool City::getHasCreateUnit()
{
    return this->hasCreateUnit;
}

/*!
 * \brief City::getIsTaken
 * \return a boolean value to know if the city is taken by an other player
 */
bool City::getIsTaken()
{
    return this->isTaken;
}

/*!
 * \brief City::getDefenceBonus
 * \return the defence bonus of the city
 */
int City::getDefenceBonus()
{
    return this->defenceBonus;
}

/*!
 * \brief City::setHasCreateUnit, set the value of hasCreateUnit, to know that the city has create a unit or not
 * \param hasCreate
 */
void City::setHasCreateUnit(bool hasCreate)
{
    this->hasCreateUnit = hasCreate;
}

/*!
 * \brief City::setIsTaken, set the value of isTaken, to know if the city is taken by another player or not
 * \param istake
 */
void City::setIsTaken(bool istake)
{
    this->isTaken = istake;
}

/*!
 * \brief City::setName, change the name of the city
 * \param name
 */
void City::setName(string name)
{
    this->name = name;
}

City::~City()
{

}

