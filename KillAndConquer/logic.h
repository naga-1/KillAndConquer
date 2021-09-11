#ifndef LOGIC_H
#define LOGIC_H

#include <tuple>
#include <QPair>
#include <QString>
#include <vector>
#include <cmath>

#include "QString"
#include "mountain.h"
#include "grass.h"
#include "forest.h"
#include "water.h"
#include "infantry.h"
#include "archer.h"
#include "knight.h"
#include "mountedarcher.h"
#include "mountain.h"
#include "city.h"
#include "player.h"

using namespace std;

class Logic
{
private:
    QString pahtFile;
    static vector<QString> colorPlayers;
    static vector<int>     costUnits;
    vector<vector<Case*>> logicMap;
    vector<Player*> players;
    int currentPlayerId;
    int nbPlayers;
    int nbCities;
    int tour;

    vector<Player*> createPlayers();
    vector<vector<Case*>> createMap(QString levelPath);
    bool isCaseInMap(int x, int y);

    int getCaseMovingBonusOfUnit(int x, int y, int unitId);
    int getCaseDamageBonusOfUnit(int x, int y, int unitId);
    int getCaseBetweenBonusUnit(int x1, int y1,int xu, int yu, int unitId);

    bool getCaseBetweenBonusUnit2(int x1, int y1,int xu, int yu, int unitId);
    bool recCaseBetweenBonusUnitIsSame(int x1, int y1,int xu, int yu, int unitId);

    tuple<int,int,int,int,int>  attack(int x1, int y1, int x2, int y2);

    void incrementTour();

public:
    Logic(QString levelPath, int nbPlayer);

    void readMap();
    QString getFilePath();

    int getCurrentPlayerId();
    int getCurrentPlayerEco();
    int getCostUnit(int id);

    bool isCity(int x, int y, int length);
    // on fait confiance à vue, elle doit vérifier que city existe avant d'appeller les méthodes
    int getCityOwner(int x, int y, int length);
    QString getCityColor(int x, int y, int length);
    bool canCreate(int x, int y, int length);

    bool isUnit(int x, int y, int length);
    // on fait confiance à vue, elle doit vérifier que l'unité existe avant d'appeller les méthodes
    int getUnitId(int x, int y, int length);
    int getUnitOwner(int x, int y, int length);
    QString getUnitColor(int x, int y, int length);
    vector<QPair<int,int>> getUnitMoveCoords(int x, int y, int length);
    vector<QPair<int,int>> getUnitAttackCoords(int x, int y, int length);
    vector<QPair<int,int>> getUnitMergeCoords(int x, int y, int length);
    int getUnitHP(int x, int y, int length);
    int getUnitMaxHP(int x, int y, int length);
    void setUnitHP(int x, int y, int length);
    void createUnit(int x, int y, int length, int PlayerId, int UnitId);

    bool isCase(int x, int y, int length);
    // on fait confiance à vue, elle doit vérifier que la case existe avant d'appeller les méthodes
    int getCaseId(int x, int y, int length);
    void setUnit(int x, int y, int length, Unit *unite);
    bool getHasMoved(int x, int y, int length);
    bool getHasAttacked(int x, int y, int length);
    void setHasAttacked(int x, int y, int length);
    int getTour();

    tuple<int,int,int,int,int>  moveUnit(int x1, int y1, int x2, int y2, int length);
    void nextPlayer();
    vector<QPair<int,int>> getTakenCityCoords();
    QString checkEnd();
};

#endif // LOGIC_H
