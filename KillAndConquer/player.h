#ifndef PLAYER_H
#define PLAYER_H
#include <QString>
using namespace std;

class Player
{
private:
    int playerNumber;
    QString playerColor;
    int playerMoney;
    int nbOfCity;
    int nbOfUnit;

public:
    Player(int, QString, int);

    int getPlayerNumber();
    QString getPlayerColor();
    int getPlayerMoney();
    int getNbOfCity();
    int getNbUnit();

    void addPlayerMoney(int);
    void incrementNbOfCity(int num);
    void incrementNbUnit(int num);
};

#endif // PLAYER_H
