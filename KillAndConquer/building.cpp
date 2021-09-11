#include "building.h"

// building Class

/*!
 * \brief Building::Building, constructor of a building
 * \param player, player who own the building
 * \param moneyPerTurn, amount of money that the building generate at each round
 */
Building::Building(int player, int moneyPerTurn = 0)
{
    this->owner=player;
    this->moneyPerTurn=moneyPerTurn;
}

/*!
 * \brief Building::getOwner
 * \return owner of the building
 */
int Building::getOwner()
{
    return this->owner;
}

/*!
 * \brief Building::getMoney
 * \return amount of money the building generate in one round
 */
int Building::getMoney()
{
    return this->moneyPerTurn;
}

/*!
 * \brief Building::setOwner, modify the owner of the building
 * \param playerId
 */
void Building::setOwner(int playerId)
{
    this->owner = playerId;
}

/*!
 * \brief Building::setMoneyPerTurn, modify the amount of money the building generate each round
 * \param m
 */
void Building::setMoneyPerTurn(int m)
{
    if(m <0)                        // negative amount of money is forbidden
    {
        this->moneyPerTurn = 0;
    }
    else
    {
        this->moneyPerTurn = m;
    }
}

Building::~Building()
{

}
