#ifndef CASE_H
#define CASE_H
#include "building.h"
#include "unit.h"

#include <vector>
using namespace std;

class Case
{

protected:
    int posX;
    int posY;
    int id;
                                    // https://www.delftstack.com/fr/howto/cpp/cpp-check-if-pointer-is-null/
   // vector<vector<bool>> vec; // https://www.geeksforgeeks.org/2d-vector-in-cpp-with-user-defined-size/
    vector<bool> fogForPlayers;
    vector<int> movingBonusUnits; //per unit
    vector<int> damageBonusUnits; //per unit

    Unit* unit;
    Building* building;


public:
    Case();
    //virtual ~Case();
    void removeFogForPlayer(int);

    int getId();
    int getPosX();
    int getPosY();
    bool getFogForPlayer(int);
    int getMovingBonusUnit(int);
    int getDamageBonusUnit(int);

    Unit* getUnit();
    void setUnit(Unit* unit);
    Building* getBuilding();



};

#endif // CASE_H
