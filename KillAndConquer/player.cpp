#include "player.h"

/*!
 * \brief Player::Player, constructor of a player
 * \param number, id of thr player
 * \param color, color of the player
 * \param money, money (economy) that the player own
 */
Player::Player(int number, QString color, int money)
{
    this->playerNumber=number;
    this->playerColor=color;
    this->playerMoney=money;
    this->nbOfCity = 0;
    this->nbOfUnit = 0;
}

/*!
 * \brief Player::getPlayerNumber
 * \return id of the player
 */
int Player::getPlayerNumber()
{
    return this->playerNumber;
}

/*!
 * \brief Player::getPlayerColor
 * \return color of the player
 */
QString Player::getPlayerColor()
{
    return this->playerColor;
}

/*!
 * \brief Player::getPlayerMoney
 * \return money that the player has
 */
int Player::getPlayerMoney()
{
    return this->playerMoney;
}

int Player::getNbOfCity()
{
    return this->nbOfCity;
}

int Player::getNbUnit()
{
    return this->nbOfUnit;
}

void Player::incrementNbOfCity(int num)
{
    this->nbOfCity += num;
    if( this->nbOfCity < 0)
    {
         this->nbOfCity = 0;
    }
}

void Player::incrementNbUnit(int num)
{
    this->nbOfUnit += num;
    if( this->nbOfUnit < 0)
    {
         this->nbOfUnit = 0;
    }
}

/*!
 * \brief Player::addPlayerMoney, set the amount of money of the player
 * \param money
 */
void Player::addPlayerMoney(int money)
{
    this->playerMoney += money;
}
