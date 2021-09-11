#include "unit.h"

// Class unit

//ADD ID FOR UNIT (INT)


/*!
 * \brief Unit::Unit, constructor of unit, unit is extented of Entity, thus we have to use firstly the constructor of Entity
 * \param id id of the unit (it can be an infantery, an archer, a knight or a mounted archer)
 * \param player id of the player associated to the unit
 * \param x coordinate x of the entity into the map (logicMap)
 * \param y coordinate y of the entity into the map (logicMap)
 * \param hp integer representing health points of an unit
 * \param damage  integer representing the amount of damage made by an unit
 * \param damageRadius integer representing the number of case radius where the unit can hit
 * \param movingRadius integer representing the number of case radius where the unit can move
 */
Unit::Unit(int id, int player, int x, int y, int hp, int damage, int damageRadius, int movingRadius) : Entity()
{
    this->id = id;
    this->maxHp = hp;
    this->hp = hp;
    this->damage = damage;
    this->damageRadius = damageRadius;
    this ->movingRadius = movingRadius;

    this->NumberOfKills = 0;
    this->hasMoved = false;
    this->hasAttacked = false;
    this->isDead = false;

    this->owner = player;
    this->posX = x;
    this->posY = y;
}

/*!
 * \brief Unit::Unit
 */
Unit::Unit() : Entity()
{

}

/*!
 * \brief Unit::getId, getter of id of unit, returns an integer
 * \return id of the unit
 */
int Unit::getId()
{
    return this->id;
}

/*!
 * \brief Unit::getHp, getter of health points, returns an integer
 * \return hp of the unit
 */
int Unit::getHp()
{
    return this->hp;
}

/*!
 * \brief Unit::getMaxHp, getter of max health points, returns an integer
 * \return max hp of the unit
 */
int Unit::getMaxHp()
{
    return this->maxHp;
}

/*!
 * \brief Unit::getdamage, getter of damage made by an unit, returns an integer
 * \return damage made by an unit
 */
int Unit::getdamage()
{
    return this->damage;
}

/*!
 * \brief Unit::getNumberOfKills, getter of the number of kills made by an unit, returns a integer
 * \return numbers of kills made by the unit
 */
int Unit::getNumberOfKills()
{
    return this->NumberOfKills;
}

//
/*!
 * \brief Unit::getDamageRadius, getter of the damage radius of an unit, returns an integer
 * \return the damage radius of an unit
 */
int Unit::getDamageRadius()
{
    return this->damageRadius;
}

/*!
 * \brief Unit::getMovingRadius, getter of the moving radius of an unit, returns an integer
 * \return the moving radius of an unit
 */
int Unit::getMovingRadius()
{
    return this->movingRadius;
}

/*!
 * \brief Unit::getHasMoved, getter of a boolean value to know if we have moved the unit
 * \return a boolean value to know if the unit has moved
 */
bool Unit::getHasMoved()
{
    return this->hasMoved;
}

/*!
 * \brief Unit::getHasAttacked, getter of a boolean value to know if the unit has attacked
 * \return a boolean value to know if the unit has attacked
 */
bool Unit::getHasAttacked()
{
    return this->hasAttacked;
}

/*!
 * \brief Unit::isUnitDead, getter of a boolean value to know if the unit is dead
 * \return a boolean value to know if the unit is dead
 */
bool Unit::isUnitDead()
{
    return this->isDead;
}

/*!
 * \brief Unit::moveTo, move unit to a position x and y
 * \param x, x position in the map (logicMap)
 * \param y, y position in the map (logicMap)
 */
void Unit::moveTo(int x, int y)
{
    this->setPosX(x);
    this->setPosY(y);
}

/*!
 * \brief Unit::setHp, private setter of health points of an unit
 * \param hp, integer representing the new hp of the unit
 */
void Unit::setHp(int hp)
{
    this->hp = hp;
}

/*!
 * \brief Unit::AddOneKill, increment the number of kills made by the unit
 */
void Unit::AddOneKill()
{
    this->NumberOfKills += 1;
    HealUnitOrNot();
}

/*!
 * \brief Unit::setHasMoved, set the boolean value has the unit moved to true
 */
void Unit::setHasMoved()
{
    this->hasMoved=true;
}

/*!
 * \brief Unit::setHasAttacked, set the boolean value has the unit attacked to true
 */
void Unit::setHasAttacked()
{
    this->hasAttacked=true;
}

/*!
 * \brief Unit::resetHasMoved, set the boolean value has the unit moved to false
 */
void Unit::resetHasMoved()
{
    this->hasMoved=false;
}

/*!
 * \brief Unit::resetHasAttacked, set the boolean value has the unit attacked to true
 */
void Unit::resetHasAttacked()
{
    this->hasAttacked=false;
}


/*!
 * \brief Unit::setIsDead, set is unit dead to true
 */
void Unit::setIsDead()
{
    this->isDead = true;
}

/*!
 * \brief Unit::UpgradeUnit, heal an unit if it reach 3 kills
 */
void Unit::HealUnitOrNot()
{
    if(this->getNumberOfKills()==3)
    {
        this->hp=this->maxHp;// revenir dessus
    }
}

/*!
 * \brief Unit::takeDamage, method to apply damages taken by the unit
 * \param damage integer representing damages taken by this unit
 */
void Unit::takeDamage(int damage)
{
    if(this->getHp() - damage <= 0)
    {
        this->setHp(0);
        this->setIsDead();
    }
    else if(damage > 0)
    {
        this->setHp((int)this->getHp() - damage);
    }
}


/*!
 * \brief Unit::operator ==, overload == operator, two unit are equals if id and owner are equal
 * \param b
 * \return true or false
 */
bool Unit::operator==(Unit* b)
{
    if(this->id == b->id && this->owner == b->owner)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
 * \brief Unit::operator +, sum of 2 units, merge into one unit and mad sum of hp of both units
 * \param b other unit*
 */
void Unit::operator+(Unit* b)
{
    this->setHp(this->getHp() + b->getHp());
    delete b;
    b = nullptr;
}
