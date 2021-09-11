#include "forest.h"

vector<int> Forest::mb = {1, 1, 0, 0};
vector<int> Forest::db = {1, 1, 0, 0};

/*!
 * \brief Forest::Forest, constructor of a forest case
 * \param x, x position of the case in the map (logicMap)
 * \param y, y position of the case in the map (logicMap)
 * \param nbPlayer, number of players playing
 * \param building (ptr), building on the case
 * \param unit (ptr), unit on the case
 */
Forest::Forest(int x, int y, int nbPlayer, Building* building, Unit* unit) : Case()
{
    this->id = 2;
    this->posX = x;
    this->posY = y;
    this->building = building;
    this->unit = unit;
    this->movingBonusUnits = mb;
    this->damageBonusUnits = db;
    this->fogForPlayers.assign(nbPlayer, true);
}
