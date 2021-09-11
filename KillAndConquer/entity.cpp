#include "entity.h"

// entity Class

/*!
 * \brief Entity::Entity, empty constructor of an entity
 */
Entity::Entity()
{
}


/*!
 * \brief Entity::getOwner, getter of the player who have the entity
 * \return the owner of the entity
 */
int Entity::getOwner()
{
    return this->owner;
}

//
/*!
 * \brief Entity::getPosX, getter of the position x of the entity into the map (logicMap)
 * \return  the x position in the map
 */
int Entity::getPosX()
{
    return this->posX;
}

/*!
 * \brief Entity::getPosy, getter of the position y of the entity into the map (logicMap)
 * \return the y position in the map
 */
int Entity::getPosy()
{
    return this->posY;
}

/*!
 * \brief Entity::setPosX, setter of the position x of the entity into the map (logicmap)
 * \param x, the x position of the entity in the map
 */
void Entity::setPosX(int x)
{
    this->posX = x;
}

/*!
 * \brief Entity::setPosY, setter of the position y of the entity into the map (logicMap)
 * \param y, the y position of the entity in the map
 */
void Entity::setPosY(int y)
{
     this->posX = y;
}

/*!
 * \brief Entity::setPlayer, setter of the player having the entity
 * \param player, id of the owner of the unit
 */
void Entity::setPlayer(int player)
{
    this->owner = player;
}
