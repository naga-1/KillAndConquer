#include "grass.h"

vector<int> Grass::mb = {0, 0, 1, 1};
vector<int> Grass::db = {1, 0, 1, 0};

/*!
 * \brief Grass::Grass, constructor of a grass case
 * \param x, x position of the case in the map (logicMap)
 * \param y, y position of the case in the map (logicMap)
 * \param nbPlayer, number of players playing
 * \param building (ptr), building on the case
 * \param unit (ptr), unit on the case
 */
Grass::Grass(int x, int y, int nbPlayer, Building* building, Unit* unit) : Case()
{
    this->id = 1;
    this->posX = x;
    this->posY = y;
    this->building = building;
    this->unit = unit;
    this->movingBonusUnits = mb;
    this->damageBonusUnits = db;
    this->fogForPlayers.assign(nbPlayer, false);
}
