#ifndef DATABUILDING_H
#define DATABUILDING_H
#include <string>
using namespace std;

class Building{

protected:
    int owner;
    int moneyPerTurn;

public:
    Building(int, int);

    int getOwner();
    int getMoney();
    void setOwner(int);
    void setMoneyPerTurn(int);

    virtual ~Building();

};

#endif // DATABUILDING_H
