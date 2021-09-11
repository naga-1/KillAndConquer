#include "mountain.h"

vector<int> Mountain::mb = {0, 0, -1, -1};
vector<int> Mountain::db = {1, 1, 0, 0};

/*!
 * \brief Mountain::Mountain, constructor of a mountain case
 * \param x, x position of the case in the map (logicMap)
 * \param y, y position of the case in the map (logicMap)
 * \param nbPlayer, number of players playing
 * \param building (ptr), building on the case
 * \param unit (ptr), unit on the case
 */
Mountain::Mountain(int x, int y, int nbPlayer, Building* building, Unit* unit) : Case()
{
    this->id = 3;
    this->posX = x;
    this->posY = y;
    this->building = building;
    this->unit = unit;
    this->movingBonusUnits = mb;
    this->damageBonusUnits = db;
    this->fogForPlayers.assign(nbPlayer, false);
}
