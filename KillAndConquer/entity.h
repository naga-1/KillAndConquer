#ifndef ENTITY_H
#define ENTITY_H
#include <string>
using namespace std;

// header of class entity
class Entity
{
protected:

    int owner;
    int posX;
    int posY;

public:

    Entity();

   int getOwner();
   int getPosX();
   int getPosy();

   void setPosX(int x);
   void setPosY(int y);
   void setPlayer(int player);
};

#endif // ENTITY_H
