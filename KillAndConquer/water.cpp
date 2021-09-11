#include "water.h"

vector<int> Water::mb = {-1, -1, -1, -1};
vector<int> Water::db = {0, 0, 0, 0};

/*!
 * \brief Water::Water, constructor of a water case
 * \param x, x position of the case in the map (logicMap)
 * \param y, y position of the case in the map (logicMap)
 * \param nbPlayer, number of players playing
 * \param building (ptr), building on the case
 * \param unit (ptr), unit on the case
 */
Water::Water(int x, int y, int nbPlayer, Building* building, Unit* unit) : Case()
{
    this->id = 4;
    this->posX = x;
    this->posY = y;
    this->building = building;
    this->unit = unit;
    this->movingBonusUnits = mb;
    this->damageBonusUnits = db;
    this->fogForPlayers.assign(nbPlayer, false);
}
