#include "logic.h"
#include "vect_error.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

vector<QString> Logic::colorPlayers = {"black", "blue", "red", "yellow", "green"};      // static vector of colors
vector<int> Logic::costUnits = {10,15,15,30};                                           // static vector of unit prices

/*!
 * \brief Logic::Logic, constructor of the logic interface, interface between graphic view and data classes
 * \param LevelPath path of the level
 * \param nbPlayer number of player in the game
 */
Logic::Logic(QString LevelPath, int nbPlayer)
{
    this->pahtFile = LevelPath;
    this->nbCities = 0;
    this->nbPlayers = nbPlayer;
    this->currentPlayerId = 0;
    this->players = createPlayers();
    this->logicMap = createMap(LevelPath);
    this->tour = 0;
}


// ///////////////////////////////////////////////////////////////////// private /////////////////////////////////////////////////////////////////////

/*!
 * \brief Logic::createPlayers, at the inialidation create a vector of players
 * \return a vector of players
 */
vector<Player*> Logic::createPlayers()
{
    if(this->nbPlayers>4){                                                              // max capacity for a game is 4 players
        qDebug()<<"To many number of players ! max is 4"<<endl;
        this->nbPlayers=4;
        qDebug()<<"Number of players has been set to 4 to avoid issues"<<endl;
    }
    else if(this->nbPlayers<1)                                                          // min capacity is 1 player
    {
        qDebug()<<"To few number of players ! min is 1"<<endl;
        this->nbPlayers=4;
        qDebug()<<"Number of players has been set to 1 to avoid issues"<<endl;
    }

    vector<Player*> p(this->nbPlayers);

    for(int i = 1; i<=this->nbPlayers; i++)                                             // for each player
    {
        p.at(i-1)=new Player(i,this->colorPlayers.at(i),15);                            // create and add a new player with an id (from 1 to n) and a color associated to the id (with the colorvector), and a starting amount of money
    }
    return p;
}

/*!
 * \brief Logic::createMap, create the logicMap
 * \param levelPath
 * \return a vector of vector of case (ptr), reprenting the map (logicMap)
 */
vector<vector<Case*>> Logic::createMap(QString levelPath)
{
    vector<vector<Case*>> caseMap;                                                      // init the map
    vector<Case*> CaseLine;                                                                 // init a row of the map
    int nbPlayer = this->nbPlayers;
    QFile fichier(levelPath);                                                           //open the file containig the level : :/fichiers/fichiers/level.txt
    int x = 0;
    int y = 0;

    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);
        while(!flux.atEnd())
        {
            QString temp = flux.readLine();                                             //read file line by line

            QTextStream ligne(&temp);
            QString word;
            x = 0;
            while(! ligne.atEnd())                                                      //read each word of each line
            {
                ligne >> word;

                if(word=="f")                                                           // add a specific case in function of the word
                {
                    CaseLine.push_back(new Forest(x,y,nbPlayer,nullptr,nullptr));
                    //qDebug()<<"forest";
                }
                else if(word=="g")
                {
                    CaseLine.push_back(new Grass(x,y,nbPlayer,nullptr,nullptr));
                    //qDebug()<<"grass";
                }
                else if(word=="w")
                {
                    CaseLine.push_back(new Water(x,y,nbPlayer,nullptr,nullptr));
                   // qDebug()<<"water";
                }
                else if(word=="m")
                {
                    CaseLine.push_back(new Mountain(x,y,nbPlayer,nullptr,nullptr));

                    //qDebug()<<"mont";
                }
                else if(word=="v")
                {
                    CaseLine.push_back(new Grass(x,y,nbPlayer,new City(0,"city") ,nullptr));
                    this->nbCities +=1;
                    //qDebug()<<"neutral city";
                }
                else if(word=="vb")
                {
                    CaseLine.push_back(new Grass(x,y,nbPlayer,new City(1,"city") ,nullptr));
                    this->players.at(0)->incrementNbOfCity(1);
                    this->nbCities +=1;
                    //qDebug()<<"blue city";
                }
                else if(word=="vr")
                {
                    CaseLine.push_back(new Grass(x,y,nbPlayer,new City(2,"city") ,nullptr));
                    this->players.at(1)->incrementNbOfCity(1);
                    this->nbCities +=1;
                    //qDebug()<<"red city";
                }
                else if(word=="vy")
                {
                    CaseLine.push_back(new Grass(x,y,nbPlayer,new City(3,"city") ,nullptr));
                    this->players.at(2)->incrementNbOfCity(1);
                    this->nbCities +=1;
                    //qDebug()<<"yellow city";
                }
                else if(word=="vg")
                {
                    CaseLine.push_back(new Grass(x,y,nbPlayer,new City(4,"city") ,nullptr));
                    this->players.at(3)->incrementNbOfCity(1);
                    this->nbCities +=1;
                    //qDebug()<<"green city";
                }

                x += 1;                                                                 // increase by increment the x position
            }
            caseMap.push_back(CaseLine);                                                // push the Caseline into the caseMap
            CaseLine.clear();                                                           // empty the case line
            y += 1;                                                                     // increase by increment the y position
        }
        fichier.close();
    }

    return caseMap;
}

/*!
 * \brief Logic::isCaseInMap, return a boolean value to know if the case exist in the map
 * \param x x position of a case in map (logicMap)
 * \param y y position of a case in map (logicMap)
 * \return a boolean value true if the case exist
 */
bool Logic::isCaseInMap(int x, int y)
{
    if(x>= 0 && x<(int)(this->logicMap.at(0).size()) && y>=0 && y<(int)(this->logicMap.size())) // if case is not out of bound
    {
        return true;
        qDebug()<<"true"<<endl;
    }
    else
    {
        return false;
    }
}

/*!
 * \brief Logic::getCaseMovingBonusOfUnit, returns the moving bonus of the case for the given unit
 * \param x x position of a case in map (logicMap)
 * \param y y position of a case in map (logicMap)
 * \param unitId id of an unit
 * \return the moving bonus of the case for the given unit
 */
int Logic::getCaseMovingBonusOfUnit(int x, int y, int unitId)
{
    return this->logicMap.at(y).at(x)->getMovingBonusUnit(unitId);                      // get the case in the logicMap and call its method
}

/*!
 * \brief Logic::getCaseDamagegBonusOfUnit, returns the damage bonus of the case for the given unit
 * \param x x position of a case in map (logicMap)
 * \param y y position of a case in map (logicMap)
 * \param unitId id of an unit
 * \return the damage bonus of the case for the given unit
 */
int Logic::getCaseDamageBonusOfUnit(int x, int y, int unitId)
{
    return this->logicMap.at(y).at(x)->getDamageBonusUnit(unitId);                      // get the case in the logicMap and call its method
}

/*!
 * \brief Logic::getCaseBetweenBonusUnit, return the moving bonus of the case next to case x1,y1 which is between case x1 y1 and the case where the unit is (xu, yu)
 * \param x1 x position of a case in map (logicMap)
 * \param y1 y position of a case in map (logicMap)
 * \param xu x position of an unit (i.e also a case) in map (logicMap)
 * \param yu y position of an unit (i.e also a case) in map (logicMap)
 * \param unitId id of an unit
 * \return the moving nonus of the case next to case x1/y1 which is between case x1/y1 and the case where the unit is (xu/yu)
 */
int Logic::getCaseBetweenBonusUnit(int x1, int y1, int xu, int yu, int unitId)
{
    int x, y;

    if(abs(x1-xu)>abs(y1-yu))                                                           // if delta x > delta y, we take the case on x axe
    {
        if(x1 < xu)
        {
            x = x1 + 1;                                                                 // if x1 < xu, x pos of case between is x1+1
        }
        else                                                                            // else x1-1
        {
            x = x1 - 1;
        }
        y = y1;
    }
    else if(abs(x1-xu)<abs(y1-yu))                                                      // if delta y > delta x, we take the case on y axe
    {
        if(y1 < yu)
        {
            y = y1 + 1;                                                                 // if y1 < yu, y pos of case between is y1+1
        }
        else                                                                            // else y1-1
        {
            y = y1 - 1;
        }
        x = x1;
    }
    else                                                                                // if delta x == delta y we calculate x AND y in the same way as before
    {
        if(x1 < xu)
        {
            x = x1 + 1;
        }
        else
        {
            x = x1 - 1;
        }
        if(y1 < yu)
        {
            y = y1 + 1;
        }
        else
        {
            y = y1 - 1;
        }
    }
    return logicMap.at(y).at(x)->getMovingBonusUnit(unitId);                        // return the moving bonus of the case at position x and y
}

/*!
 * \brief Logic::getCaseBetweenBonusUnit2, return true if one of the cases between case x1,y1 and the case where the unit is (xu, yu) have the same moving bonus
 * \param x1 x position of a case in map (logicMap)
 * \param y1 y position of a case in map (logicMap)
 * \param xu x position of an unit (i.e also a case) in map (logicMap)
 * \param yu y position of an unit (i.e also a case) in map (logicMap)
 * \param unitId id of an unit
 * \return boolean value true if one of the cases between x1/y1  and xu/yu have the same moving bonus
 */
bool Logic::getCaseBetweenBonusUnit2(int x1, int y1, int xu, int yu, int unitId)
{
        int a1,b1, a2,b2, a3,b3;
        int bonus = getCaseMovingBonusOfUnit(xu, yu, unitId);

        // we have to take two or three cases between cases x1, y1 and xu, yu in fonction of different configuration
        if(abs(x1-xu)>abs(y1-yu))                                                       // if delta x > delta y, we take cases on x axe
        {
            if(x1 < xu)                                                                 // if x1 < xu, x pos of cases between are x1+1
            {
                a1 = x1 + 1; a2 =a1; a3 = a1;
            }
            else                                                                        // else x1 > xu, x pos of cases between are x1-1
            {
                 a1 = x1 - 1; a2 =a1; a3 = a1;
            }

            b1 = y1; b2 = y1 +1; b3 = y1 -1;                                            // take 3 cases of different y coord around the position y of y1

            if(y1 < yu)                                                                 // in function of the position of y we take two or three cases and we look at their moving bonus
            {
                return true  && (getCaseBetweenBonusUnit(a1, b1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(a2, b2, xu, yu, unitId) == bonus);
            }
            else if(y1 > yu)
            {
                return true  && (getCaseBetweenBonusUnit(a1, b1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(a3, b3, xu, yu, unitId) == bonus);
            }
            else
            {
                return true  && (getCaseBetweenBonusUnit(a1, b1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(a3, b3, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(a2, b2, xu, yu, unitId) == bonus);
            }
        }
        else if(abs(x1-xu)<abs(y1-yu))                                                  // if delta x < delta y, we take cases on y axe
        {
            if(y1 < yu)                                                                 // if y1 < yu, y pos of cases between are y1+1
            {
                b1 = y1 + 1; b2 = b1; b3 = b1;
            }
            else                                                                        // else y1 > yu, y pos of cases between are y1-1
            {
                b1 = y1 - 1; b2 = b1; b3 = b1;
            }
            a1 = x1; a2 = x1 +1; a3 = x1 -1;                                            // take 3 cases of different x coord around the position x of x1

            if(x1 < xu)                                                                 // in function of the position of y we take two or three cases and we look at their moving bonus
            {
                return true  && (getCaseBetweenBonusUnit(a1, b1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(a2, b2, xu, yu, unitId) == bonus);
            }
            else if(x1 > xu)
            {
                return true  && (getCaseBetweenBonusUnit(a1, b1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(a3, b3, xu, yu, unitId) == bonus);
            }
            else
            {
                return true  && (getCaseBetweenBonusUnit(a1, b1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(a3, b3, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(a2, b2, xu, yu, unitId) == bonus);
            }
        }
        else                                                                            // if delta x = delta y, we are on a corner, we have find which one and look at the moving bonuses of the cases selected
        {
            if(x1 < xu && y1 < yu)
            {
                return true  && (getCaseBetweenBonusUnit(x1+1, y1+1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(x1, y1+1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(x1+1, y1, xu, yu, unitId) == bonus);
            }
            else if(x1 > xu && y1 < yu)
            {
                return true  && (getCaseBetweenBonusUnit(x1-1, y1+1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(x1-1, y1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(x1, y1+1, xu, yu, unitId) == bonus);
            }
            else if(x1 > xu && y1 > yu)
            {
                return true  && (getCaseBetweenBonusUnit(x1-1, y1-1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(x1-1, y1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(x1, y1-1, xu, yu, unitId) == bonus);
            }
            else
            {
                return true  && (getCaseBetweenBonusUnit(x1+1, y1-1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(x1+1, y1, xu, yu, unitId) == bonus || getCaseBetweenBonusUnit(x1, y1-1, xu, yu, unitId) == bonus);

            }
        }

}

/*!
 * \brief Logic::recCaseBetweenBonusUnitIsSame, a boolean value, true if there is a path of a same moving bonus between case x1, y1 and case xu, yu
 * \param x1 x position of a case in map (logicMap)
 * \param y1 y position of a case in map (logicMap)
 * \param xu x position of an unit (i.e also a case) in map (logicMap)
 * \param yu y position of an unit (i.e also a case) in map (logicMap)
 * \param unitId id of an unit
 * \return a boolean value true if there is a path of a same moving bonus between case x1/y1 and case xu/yu
 */
bool Logic::recCaseBetweenBonusUnitIsSame(int x1, int y1, int xu, int yu, int unitId)
{
    if(getCaseBetweenBonusUnit(x1, y1, xu, yu, unitId) != getCaseMovingBonusOfUnit(xu, yu, unitId)) // if not the same bonus
    {
        return false;
    }
    if(getCaseBetweenBonusUnit2(x1, y1, xu, yu, unitId) && (abs(x1 - xu) == 2 || abs(y1 - yu) == 2 )) // if there is path and we are next to the unit
    {
        return true;
    }
    else                                                                                // same as getCaseBetweenBonusUnit2 before but recursively
    {
        int a1,b1, a2,b2, a3,b3;

        if(abs(x1-xu)>abs(y1-yu))
        {
            if(x1 < xu)
            {
                a1 = x1 + 1; a2 =a1; a3 = a1;
            }
            else
            {
                 a1 = x1 - 1; a2 =a1; a3 = a1;
            }

            b1 = y1; b2 = y1 +1; b3 = y1 -1;
            if(y1 < yu)
            {
                return true  && (recCaseBetweenBonusUnitIsSame(a1, b1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(a2, b2, xu, yu, unitId));
            }
            else if(y1 > yu)
            {
                return true  && (recCaseBetweenBonusUnitIsSame(a1, b1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(a3, b3, xu, yu, unitId));
            }
            else
            {
                return true  && (recCaseBetweenBonusUnitIsSame(a1, b1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(a3, b3, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(a2, b2, xu, yu, unitId));
            }
        }
        else if(abs(x1-xu)<abs(y1-yu))
        {
            if(y1 < yu)
            {
                b1 = y1 + 1; b2 = b1; b3 = b1;
            }
            else
            {
                b1 = y1 - 1; b2 = b1; b3 = b1;
            }
            a1 = x1; a2 = x1 +1; a3 = x1 -1;
            if(x1 < xu)
            {
                return true  && (recCaseBetweenBonusUnitIsSame(a1, b1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(a2, b2, xu, yu, unitId));
            }
            else if(x1 > xu)
            {
                return true  && (recCaseBetweenBonusUnitIsSame(a1, b1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(a3, b3, xu, yu, unitId));
            }
            else
            {
                return true  && (recCaseBetweenBonusUnitIsSame(a1, b1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(a3, b3, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(a2, b2, xu, yu, unitId));
            }
        }
        else
        {
            if(x1 < xu && y1 < yu)
            {
                return true  && (recCaseBetweenBonusUnitIsSame(x1+1, y1+1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(x1, y1+1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(x1+1, y1, xu, yu, unitId));
            }
            else if(x1 > xu && y1 < yu)
            {
                return true  && (recCaseBetweenBonusUnitIsSame(x1-1, y1+1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(x1-1, y1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(x1, y1+1, xu, yu, unitId));
            }
            else if(x1 > xu && y1 > yu)
            {
                return true  && (recCaseBetweenBonusUnitIsSame(x1-1, y1-1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(x1-1, y1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(x1, y1-1, xu, yu, unitId));
            }
            else
            {
                return true  && (recCaseBetweenBonusUnitIsSame(x1+1, y1-1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(x1+1, y1, xu, yu, unitId) || recCaseBetweenBonusUnitIsSame(x1, y1-1, xu, yu, unitId));

            }
        }

        return true;
    }
}

/*!
 * \brief Logic::incrementTour, increment number of the round
 */
void Logic::incrementTour()
{
    tour = tour + 1;
}

/*!
 * \brief Logic::attack, returns in a tuple a flag and two pair of coordinates (for each unit)
 * \param x1 x position of the attacker in the map (logicMap)
 * \param y1 y position of the attacker in the map (logicmap)
 * \param x2 x position of the attacked unit in the map (logicMap)
 * \param y2 y position of tne attacked unit in the map (logicMap)
 * \return a tuple consist of a flag and two pair of coordinates (for each unit)
 */
tuple<int,int,int,int,int> Logic::attack(int x1, int y1, int x2, int y2)
{
    float damage;
    float percentage;
    float healthRatio = (float)logicMap.at(y1).at(x1)->getUnit()->getHp() / (float)logicMap.at(y1).at(x1)->getUnit()->getMaxHp(); // make the ratio hp/hpmax of the attacker

    if(healthRatio >= 0.5)                                                              // in fonction of this ratio calculate a percentage
    {
        percentage = 1.;
    }
    else if(healthRatio >= 0.4)
    {
        percentage = 0.8;
    }
    else if(healthRatio >= 0.3)
    {
        percentage = 0.6;
    }
    else if(healthRatio >= 0.2)
    {
        percentage = 0.4;
    }
    else
    {
        percentage = 0.1;
    }

    damage = percentage * (float)logicMap.at(y1).at(x1)->getUnit()->getdamage();               // this percentage is multiplied by the damaged that the unit can do
    damage += damage * 0.1 * (float)logicMap.at(y1).at(x1)->getDamageBonusUnit( logicMap.at(y1).at(x1)->getUnit()->getId() ); // damage are multiplied by 0.1 * bonus of the case for the unit

    if(logicMap.at(y2).at(x2)->getBuilding()!= nullptr)                                        // If player adverse is on it's own city, the city give it a defence bonus
    {
        City* city = dynamic_cast<City*>(logicMap.at(y2).at(x2)->getBuilding());
        if(city->getOwner() == logicMap.at(y2).at(x2)->getUnit()->getOwner())
        {
            damage -= 0.1 * (float) city->getDefenceBonus();
        }
    }

    logicMap.at(y2).at(x2)->getUnit()->takeDamage( int (ceil(damage)));                 // add damage to the unit attacked

    logicMap.at(y1).at(x1)->getUnit()->setHasMoved();                                   // set flags to the attacker
    logicMap.at(y1).at(x1)->getUnit()->setHasAttacked();

    if(logicMap.at(y2).at(x2)->getUnit()->isUnitDead())                                 // if adverse unit is dead
    {
       players.at(logicMap.at(y2).at(x2)->getUnit()->getOwner()-1)->incrementNbUnit(-1);// sub 1 unit of the total unit of the player (i.e owner) of this unit
       logicMap.at(y2).at(x2)->setUnit(nullptr);                                        // erase it
       logicMap.at(y1).at(x1)->getUnit()->AddOneKill();                                 // increment nb of kill of unit (if reach 3, the unit is heal)

       if(logicMap.at(y2).at(x2)->getMovingBonusUnit(logicMap.at(y1).at(x1)->getUnit()->getId()) != -1 && logicMap.at(y1).at(x1)->getUnit()->getId() != 2  && logicMap.at(y1).at(x1)->getUnit()->getId() != 4) // if attacker unit can move on case where adverse unit is and unit is not an (mounted)archer
       {
           logicMap.at(y1).at(x1)->getUnit()->moveTo(x2,y2);                            // set new x,y coord
           logicMap.at(y2).at(x2)->setUnit( logicMap.at(y1).at(x1)->getUnit() );        // move unit to next case
           logicMap.at(y1).at(x1)->setUnit(nullptr);                                    // remove unit from case, will delete also ?
           return make_tuple(1,x2,y2,x2,y2);                                            // 1 -> b is dead an a take is place, xa, ya, xb, yb
       }
       else                                                                             // else, if unit can't move
       {
           qDebug()<<x1<<y1<<x2<<y2<<endl;
           return make_tuple(3,x1,y1,x2,y2);                                            // 3 -> b is dead an a don't take is place, xa, ya, xb, yb
       }
    }

    else if((abs(x1-x2) <= 1 && abs (y1-y2) <= 1) || logicMap.at(y2).at(x2)->getUnit()->getId() == 2 || logicMap.at(y2).at(x2)->getUnit()->getId() == 4) // if unit attacked is next to the other unit or has an arc, then the unit reply to the attack
    {
        healthRatio = (float)logicMap.at(y2).at(x2)->getUnit()->getHp() / (float)logicMap.at(y2).at(x2)->getUnit()->getMaxHp();   // same has before, compute damage

        if(healthRatio >= 0.5)
        {
            percentage = 1.;
        }
        else if(healthRatio >= 0.4)
        {
            percentage = 0.8;
        }
        else if(healthRatio >= 0.3)
        {
            percentage = 0.6;
        }
        else if(healthRatio >= 0.2)
        {
            percentage = 0.4;
        }
        else
        {
            percentage = 0.1;
        }

        damage = percentage * (float)logicMap.at(y2).at(x2)->getUnit()->getdamage();
        damage += damage * 0.1 * (float)logicMap.at(y2).at(x2)->getDamageBonusUnit( logicMap.at(y2).at(x2)->getUnit()->getId() ); // compute damage

        if(logicMap.at(y1).at(x1)->getBuilding()!= nullptr)                                        // If player adverse is on it's own city, the city give it a defence bonus
        {
            City* city = dynamic_cast<City*>(logicMap.at(y1).at(x1)->getBuilding());
            if(city->getOwner() == logicMap.at(y1).at(x1)->getUnit()->getOwner())
            {
                damage -= 0.1 * (float) city->getDefenceBonus();
            }
        }

        logicMap.at(y1).at(x1)->getUnit()->takeDamage( int (ceil(damage)));             // add damage

        if(logicMap.at(y1).at(x1)->getUnit()->isUnitDead())                             // if unit which takes damages is dead
        {
           players.at(logicMap.at(y1).at(x1)->getUnit()->getOwner()-1)->incrementNbUnit(-1);// sub 1 unit of the total unit of the player (i.e owner) of this unit
           logicMap.at(y1).at(x1)->setUnit(nullptr);                                    // erase it
           logicMap.at(y2).at(x2)->getUnit()->AddOneKill();                             // increment nb of kill of unit (if reach 3, the unit is heal)

           return make_tuple(2,x1,y1,-1,-1);                                            // 2 -> a is dead, xa, ya, xb, yb
         }
         else                                                                           // if none are dead
         {
           return make_tuple(0,x1,y1,-1,-1);                                            // 0 -> none are dead, xa, ya, xb, yb
         }
    }
    else
    {
        return make_tuple(0,x1,y1,-1,-1);                                               // 0 -> none are dead, xa, ya, xb, yb
    }

}


// ///////////////////////////////////////////////////////////////////// public /////////////////////////////////////////////////////////////////////

/*!
 * \brief Logic::readMap, read the map logicMap and print it in the terminal
 */
void Logic::readMap()
{
    for (vector<vector<Case*>>::iterator it = logicMap.begin(); it != logicMap.end(); ++it) // for rows in logicmap
    {
        QDebug deb = qDebug().nospace();
        for (vector<Case*>::iterator c = it->begin(); c != it->end(); ++c)                  // for cases in rows
         {
            if((*c)->getBuilding() != nullptr)
            {
                deb<<"|city |";
            }
            else if((*c)->getId() == 1)
            {
                deb<<"|grass|";
            }
            else if((*c)->getId() == 2)
            {
                deb<<"|forst|";
            }
            else if((*c)->getId() == 3)
            {
                deb<<"|mount|";
            }
            else if((*c)->getId() == 4)
            {
                deb<<"|water|";
            }
           }
        qDebug()<<" "<<endl;
    }
}

/*!
 * \brief Logic::getFilePath
 * \return pathfile of the game
 */
QString Logic::getFilePath()
{
    return this->pahtFile;
}

/*!
 * \brief Logic::getCurrentPlayerId, return id of current player (i.e player of the round)
 * \return id of current player
 */
int Logic::getCurrentPlayerId()
{
    return this->currentPlayerId;
}

/*!
 * \brief Logic::getCurrentPlayerEco, return amount of money of the current player (i.e player of the round)
 * \return amount of money of the current player
 */
int Logic::getCurrentPlayerEco()
{
    return this->players.at(this->currentPlayerId-1)->getPlayerMoney();
}

/*!
 * \brief Logic::getCostUnit, return cost of an unit
 * \param id
 * \return cost of an unit
 */
int Logic::getCostUnit(int id)
{
    if(id>0 && id <5)
    {
        return costUnits.at(id-1);
    }
    else
    {
        return -1;
    }
}

/*!
 * \brief Logic::isCity, returns a boolean value to know if there is a city on the case x,y
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return true if there is a city on this case
 */
bool Logic::isCity(int x, int y, int length)
{
    int X = x/length;                                                                   // convert position x from graphic view to logicMap
    int Y = y/length;                                                                   // convert position y from graphic view to logicMap
    if(isCaseInMap(X,Y) && logicMap.at(Y).at(X)->getBuilding() != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
 * \brief Logic::getCityOwner, return owner of the city at position x, y in graphic view
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return owner of the city at position x/y if exist
 */
int Logic::getCityOwner(int x, int y, int length)
{
    try {
        Case* c= logicMap.at(y/length).at(x/length);
        if(c->getBuilding() == nullptr) // throw error if city is null
        {
            vect_error ve("city is nullptr, can't use methods");
            throw ve;
        }
        else{
            return c->getBuilding()->getOwner();
        }

    }
    catch (const exception &e)      // if stl vector send error we cath them (i.e depassement ...)
    {
        //qDebug()<<e.what();
        throw;
    }
}

/*!
 * \brief Logic::getCityColor, returns color of the city
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return color of the city
 */
QString Logic::getCityColor(int x, int y, int length)
{
    int id;

    try     // try catch, if getCityOwner send errors we catch them (e.i stl vector error or city on case can't be reach)
    {
        id = getCityOwner(x,y,length);
    }
    catch (const exception &e)
    {
        qDebug()<<e.what();
        id = 99999;
    }
    catch (vect_error a)
    {
        qDebug()<<a.error;
        id = 99999;
    }

    if (id == 0)                                                                        // if id == 0 -> neutral city
    {
        return colorPlayers.at(id);
    }
    else if(id > 0)
    {
        return players.at(id-1)->getPlayerColor(); // or colorVector.at(id);
    }
    else
    {
        return QString::null;
    }
}

/*!
 * \brief Logic::canCreat, return a boolean value to know if a city has create an unit
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return boolean value, true if city can't create unit
 */
bool Logic::canCreate(int x, int y, int length)
{
    City* ville = dynamic_cast<City*>(logicMap.at(y/length).at(x/length)->getBuilding());
    return !ville->getHasCreateUnit();
}

/*!
 * \brief Logic::isUnit, return a boolean value to know if there is an unit on case x,y in graphic view
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return true if there is a unit on this case
 */
bool Logic::isUnit(int x, int y, int length)
{
    int X = x/length;
    int Y = y/length;                                                                   // convert pos x and y from graphic view to logicMAp
    if(isCaseInMap(X,Y) && logicMap.at(Y).at(X)->getUnit() != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
 * \brief Logic::getUnitId, return id of unit on the case x,y in the graphic view
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return id of unit if exists
 */
int Logic::getUnitId(int x, int y, int length)
{
    if(isUnit(x, y, length)) // try catch
    {
        return logicMap.at(y/length).at(x/length)->getUnit()->getId();
    }
    else
    {
        return -1;
    }
}

/*!
 * \brief Logic::getUnitOwner, return owner of unit on the case x,y in the graphic view
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return owner of unit if exists
 */
int Logic::getUnitOwner(int x, int y, int length)
{
    if(isUnit(x, y, length)) // try catch
    {
        return logicMap.at(y/length).at(x/length)->getUnit()->getOwner();
    }
    else
    {
        return -1;
    }
}

/*!
 * \brief Logic::getUnitColor, return color of unit on the case x,y in the graphic view
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return color of unit if exists
 */
QString Logic::getUnitColor(int x, int y, int length)
{
    int id = getUnitOwner(x,y,length);
    if (id == 0)
    {
        return colorPlayers.at(id);
    }
    else if(id > 0)
    {
        return players.at(id-1)->getPlayerColor(); // or colorVector.at(id);
    }
    else
    {
        return QString::null;
    }
}

// returns all coordinates where the unit can move
/*!
 * \brief Logic::getUnitMoveCoords, returns all coordinates (in logicMap) where the unit can move
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return all coordinates where the unit can move
 */
vector<QPair<int, int>> Logic::getUnitMoveCoords(int x, int y, int length)
{
    int X = x/length;                                                                   // pos X of unit in logicMap
    int Y = y/length;                                                                   // pos Y of unit in logicMap
    vector<QPair<int, int>> coords;                                                     // vector of coordinates x y
    int id = getUnitId(x,y,length);                                                     // id of unit
    int movingDiameter = (logicMap.at(Y).at(X)->getUnit()->getMovingRadius() + logicMap.at(Y).at(X)->getMovingBonusUnit(id))*2 + 1; // diameter of unit moving range
    int coordx = X - (movingDiameter-1)/2;                                              // starting coordinate x
    int coordy = Y - (movingDiameter-1)/2;                                              // starting coordinate y


    for(int i = 0; i<movingDiameter;i++)                                                // will go through the square of length = moving diameter (with x,y at the center)
    {

        for(int j = 0; j<movingDiameter;j++)
        {

            if(isCaseInMap(coordx,coordy) && getCaseMovingBonusOfUnit(coordx,coordy, id) != -1) // if case is in map and the unit is allowed to go on it (i.e movingBonus not at -1 for this unit)
            {
               if(!isUnit(coordx*length, coordy*length,length))                         // if there is not an unit on the case (case is empty)
               {
                                                                                        // if we are at a border between two bioms with different bonuses for the unit, we can enter only of one case in this new biom
                   if( (abs(coordx - X) > 1 || abs(coordy - Y) > 1 ) && recCaseBetweenBonusUnitIsSame(coordx, coordy, X, Y, id))
                    {
                        coords.push_back(qMakePair(coordx,coordy));                     // push back QPair of values (= coordinates x and y) in the vector
                    }
                   else if(abs(coordx - X) <= 1 && abs(coordy - Y) <= 1)                // if case is next to the unit
                   {
                        coords.push_back(qMakePair(coordx,coordy));                     // push back QPair of values (=coordinates x and y) in the vector
                   }
                }
            }

            coordy += 1;
        }

        coordy = Y- (movingDiameter-1)/2;                                               // reset value of coordy
        coordx+=1;                                                                      // increment x value
    }
    return coords;
}

/*!
 * \brief Logic::getUnitAttackCoords, returns all coordinates (in logicMap) where the unit can attack
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return all coordinates where the unit can attack
 */
vector<QPair<int, int> > Logic::getUnitAttackCoords(int x, int y, int length)
{
    int X = x/length;                                                                   // pos X of unit in logicMap
    int Y = y/length;                                                                   // pos Y of unit in logicMap
    vector<QPair<int, int>> coords;                                                     // vector of coordinates x y
    int id = getUnitOwner(x,y,length);                                                     // id of unit
    int AttackDiameter = logicMap.at(Y).at(X)->getUnit()->getDamageRadius()*2 + 1;      // diameter of unit range move
    int coordx = X - (AttackDiameter-1)/2;                                              // starting coordinate x
    int coordy = Y - (AttackDiameter-1)/2;                                              // starting coordinate y

    for(int i = 0; i<AttackDiameter;i++)
    {

        for(int j = 0; j<AttackDiameter;j++)                                            // will go through the square of length = moving diameter (with x,y at the center)
        {
            if(isCaseInMap(coordx,coordy) && isUnit(coordx*length, coordy*length, length) && getUnitOwner(coordx*length, coordy*length, length) != id) // if case is in map and there is an adverse unit on it
            {
                coords.push_back(qMakePair(coordx,coordy));                             // push back QPair of values (=coordinates x and y) in the vector
            }

            coordy += 1;                                                                // increment y coord
        }

        coordy = Y- (AttackDiameter-1)/2;                                               // reset value of coordy
        coordx+=1;                                                                      // increment x coord
    }
    return coords;
}

/*!
 * \brief Logic::getUnitAttackCoords, returns all coordinates (in logicMap) where the unit can merge with another one
 * \param x  x position of the case in graphic view
 * \param y  y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return all coordinates where the unit can attack
 */
vector<QPair<int, int> > Logic::getUnitMergeCoords(int x, int y, int length)
{
    int X = x/length;                                                                   // pos X of unit in logicMap
    int Y = y/length;                                                                   // pos Y of unit in logicMap
    vector<QPair<int, int>> coords;                                                     // vector of coordinates x y
    int id = getUnitId(x,y,length);                                                     // id of unit
    int movingDiameter = (logicMap.at(Y).at(X)->getUnit()->getMovingRadius() + logicMap.at(Y).at(X)->getMovingBonusUnit(id))*2 + 1; // diameter of unit moving range
    int coordx = X - (movingDiameter-1)/2;                                              // starting coordinate x
    int coordy = Y - (movingDiameter-1)/2;                                              // starting coordinate y


    for(int i = 0; i<movingDiameter;i++)                                                // will go through the square of length = moving diameter (with x,y at the center)
    {

        for(int j = 0; j<movingDiameter;j++)
        {
            if(coordx != X || coordy != Y)                                                          // if not itself
            {
                if(isCaseInMap(coordx,coordy) && getCaseMovingBonusOfUnit(coordx,coordy, id) != -1) // if case is in map and the unit is allowed to go on it (i.e movingBonus not at -1 for this unit)
                {
                   if( isUnit(coordx*length, coordy*length,length) && (*logicMap.at(Y).at(X)->getUnit())==logicMap.at(coordy).at(coordx)->getUnit() &&
                           logicMap.at(Y).at(X)->getUnit()->getHp() + logicMap.at(coordy).at(coordx)->getUnit()->getHp() <= logicMap.at(coordy).at(coordx)->getUnit()->getMaxHp() )    // if both units are equal, and sum of their hp <= max hp, they can merge
                   {
                                                                                            // if we are at a border between two bioms with different bonuses for the unit, we can enter only of one case in this new biom
                       if( (abs(coordx - X) > 1 || abs(coordy - Y) > 1 ) && recCaseBetweenBonusUnitIsSame(coordx, coordy, X, Y, id))
                       {
                            coords.push_back(qMakePair(coordx,coordy));                     // push back QPair of values (= coordinates x and y) in the vector
                       }
                       else if(abs(coordx - X) <= 1 && abs(coordy - Y) <= 1)                // if case is next to the unit
                       {
                            coords.push_back(qMakePair(coordx,coordy));                     // push back QPair of values (=coordinates x and y) in the vector
                       }
                    }
                }
            }
            coordy += 1;
        }

        coordy = Y- (movingDiameter-1)/2;                                               // reset value of coordy
        coordx+=1;                                                                      // increment x value
    }
    return coords;
}

/*!
 * \brief Logic::getUnitHP, return hp of unit on the case x,y in the graphic view
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return hp of unit if exists
 */
int Logic::getUnitHP(int x, int y, int length)
{
    return logicMap.at(y/length).at(x/length)->getUnit()->getHp();

}

/*!
 * \brief Logic::getUnitMaxHP, return max hp of unit on the case x,y in the graphic view
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return max hp of unit if exists
 */
int Logic::getUnitMaxHP(int x, int y, int length)
{
    return logicMap.at(y/length).at(x/length)->getUnit()->getMaxHp();
}

/*!
 * \brief Logic::createUnit, create an unit on the case x,y of the graphic view at the corresponding case in the logicMap
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \param PlayerId id of the owner of the unit
 * \param UnitId id of the unit
 */
void Logic::createUnit(int x, int y, int length, int PlayerId, int UnitId)
{                                                                                       // in fonction of the id create the good unit
    if(UnitId == 1){
       logicMap.at(y/length).at(x/length)->setUnit(new Infantry(PlayerId,x,y));
    }
    else if(UnitId == 2){
       logicMap.at(y/length).at(x/length)->setUnit(new Knight(PlayerId,x,y));
    }
    else if(UnitId == 3){
       logicMap.at(y/length).at(x/length)->setUnit(new Archer(PlayerId,x,y));
    }
    else if(UnitId == 4){
       logicMap.at(y/length).at(x/length)->setUnit(new mountedArcher(PlayerId,x,y));
    }
    this->players.at(this->currentPlayerId-1)->addPlayerMoney(-(costUnits.at(UnitId-1)));// remove cost of the unit from the money of the player

    players.at(PlayerId-1)->incrementNbUnit(1);
    logicMap.at(y/length).at(x/length)->getUnit()->setHasMoved();                        // set flags to the unit
    logicMap.at(y/length).at(x/length)->getUnit()->setHasAttacked();

    City* ville = dynamic_cast<City*>(logicMap.at(y/length).at(x/length)->getBuilding());
    ville->setHasCreateUnit(true);                                                       // set flag to the city
}

/*!
 * \brief Logic::isCase, return boolean value if there is a case at x,y
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return true if there is a case at position x,y
 */
bool Logic::isCase(int x, int y, int length)
{
    int X = x/length;
    int Y = y/length;
    if(isCaseInMap(X,Y))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
 * \brief Logic::getCaseId, return id of the case x,y in the graphic view
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return id of the case at position x,y
 */
int Logic::getCaseId(int x, int y, int length)
{
    return this->logicMap.at(y/length).at(x/length)->getId();
}

/*!
 * \brief Logic::getHasMoved, return boolean value to know if the unit hasmoved on the case x,y in the graphic view
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return false if unit has flag hasMoved to true
 */
bool Logic::getHasMoved(int x, int y, int length)
{
    return !(logicMap.at(y/length).at(x/length)->getUnit()->getHasMoved());
}

/*!
 * \brief Logic::getHasAttacked
 * \param x x position of the case in graphic view
 * \param y y position of the case in graphic view
 * \param length length of a case in graphic view
 * \return true if the Unit has attacked
 */
bool Logic::getHasAttacked(int x, int y, int length)
{
    return !(logicMap.at(y/length).at(x/length)->getUnit()->getHasAttacked());
}

/*!
 * \brief Logic::getTour, return round of the game
 * \return round of the game
 */
int Logic::getTour()
{
    return tour;
}

/*!
 * \brief Logic::moveUnit, returns in a tuple a flag and two pair of coordinates (for each unit) to move units on graphic view, change in logic the units also
 * \param x1 x position of the main unit in the map (logicMap)
 * \param y1 y position of the main unit in the map (logicmap)
 * \param x2 x position of the second unit (if there is one) in the map (logicMap)
 * \param y2 y position of the second unit (if there is one) in the map (logicMap)
 * \return a tuple consists of a flag and two pair of coordinates (for each unit)
 */
tuple<int,int,int,int,int>  Logic::moveUnit(int x1, int y1, int x2, int y2, int length)
{
    int X2 = x2/length;
    int Y2 = y2/length;

    if(logicMap.at(y1/length).at(x1/length)->getUnit()->getHasMoved())                  // if unit has moved it can only attack
    {
        vector<QPair<int,int>> attackCoords = getUnitAttackCoords(x1, y1, length);

        // test if unit can attack on case
        for (vector<QPair<int,int>>::iterator coord = attackCoords.begin(); coord != attackCoords.end(); ++coord) // if main unit pos x,y is in one of the coordinates of attack it attacks
        {
            if((*coord).first == X2 && (*coord).second == Y2)
            {
                return attack(x1/length,y1/length, X2, Y2);                             // attack and return new coord of units
            }
        }
        return make_tuple(0,x1/length,y1/length,-1,-1);
    }

    else                                                                                // else it can either move or attack
    {
        vector<QPair<int,int>> moveCoords = getUnitMoveCoords(x1, y1, length);
        vector<QPair<int,int>> mergeCoords = getUnitMergeCoords(x1, y1, length);
        vector<QPair<int,int>> attackCoords = getUnitAttackCoords(x1, y1, length);

        // test if unit can merge on case
        for (vector<QPair<int,int>>::iterator coord = mergeCoords.begin(); coord != mergeCoords.end(); ++coord)
        {
            if((*coord).first == X2 && (*coord).second == Y2)                                       // if main unit pos x,y is in one of the coordinates of merge it moves and merge
            {
                (*logicMap.at(y1/length).at(x1/length)->getUnit()) + logicMap.at(Y2).at(X2)->getUnit();  // merge two units with overload operator +
                logicMap.at(y1/length).at(x1/length)->getUnit()->setHasMoved();                     // set has moved to true
                logicMap.at(y1/length).at(x1/length)->getUnit()->moveTo(X2,Y2);                     // set new x,y coord
                logicMap.at(Y2).at(X2)->setUnit( logicMap.at(y1/length).at(x1/length)->getUnit() ); // move unit to next case
                logicMap.at(y1/length).at(x1/length)->setUnit(nullptr);                             // remove unit from case, will delete also

                return make_tuple(1,X2,Y2,X2,Y2);                                                   // return new coord of unit
                break;
            }
        }

        // test if unit can move on case
        for (vector<QPair<int,int>>::iterator coord = moveCoords.begin(); coord != moveCoords.end(); ++coord)
        {
            if((*coord).first == X2 && (*coord).second == Y2)                                       // if main unit pos x,y is in one of the coordinates of move it moves
            {
                logicMap.at(y1/length).at(x1/length)->getUnit()->moveTo(X2,Y2);                     // set new x,y coord
                logicMap.at(y1/length).at(x1/length)->getUnit()->setHasMoved();                     // set has moved to true
                logicMap.at(Y2).at(X2)->setUnit( logicMap.at(y1/length).at(x1/length)->getUnit() ); // move unit to next case
                logicMap.at(y1/length).at(x1/length)->setUnit(nullptr);                             // remove unit from case, will delete also
                return make_tuple(0,X2,Y2,-1,-1);                                                   // return new coord of unit
                break;
            }
        }

        // test if unit can attack on case
        for (vector<QPair<int,int>>::iterator coord = attackCoords.begin(); coord != attackCoords.end(); ++coord)   // if main unit pos x,y is in one of the coordinates of attack it attacks
        {
            if((*coord).first == X2 && (*coord).second == Y2)
            {
                return attack(x1/length,y1/length, X2, Y2);                             // attack and return new coord of units
            }
        }

                                                                                        // else return starting point
        return make_tuple(0,x1/length,y1/length,-1,-1);                                 // return old coord of unit
    }

}

/*!
 * \brief Logic::nextPlayer, change the main player (and the round if necessary), reset all the flags set in the round
 */
void Logic::nextPlayer()
{
    City* city;
    int nextPlayerId = (this->currentPlayerId) % this->nbPlayers +1;

    // while next player has no city and no units, we erase it and take the next one
     while(players.at(nextPlayerId-1)->getNbOfCity() == 0 && players.at(nextPlayerId-1)->getNbUnit() == 0)
     {
        //players.erase(players.begin()+nextPlayerId-1);
        //nbPlayers-=1;
        nextPlayerId = (nextPlayerId) % this->nbPlayers +1;
    }

    for (vector<vector<Case*>>::iterator it = logicMap.begin(); it != logicMap.end(); ++it)   // for rows in logicmap
    {
        QDebug deb = qDebug().nospace();
        for (vector<Case*>::iterator c = it->begin(); c != it->end(); ++c)                    // for cases in rows
         {
            // if a unit is on a city during one roud then the city is captured
            if((*c)->getUnit() != nullptr &&  (*c)->getBuilding() != nullptr && (*c)->getBuilding()->getOwner() != (*c)->getUnit()->getOwner() && (*c)->getUnit()->getOwner() == nextPlayerId)
            {
                if((*c)->getBuilding()->getOwner() != 0)                                       // if it is not a city of neutral player (because this player don't really exist)
                {
                    this->players.at( (*c)->getBuilding()->getOwner()-1)->incrementNbOfCity(-1);   // decrement nb of city of the player
                }
                (*c)->getBuilding()->setOwner(nextPlayerId);                                   // modify owner of city
                this->players.at(nextPlayerId-1)->incrementNbOfCity(1);                        // incremenbt nb of city of next player
                city = dynamic_cast<City*>((*c)->getBuilding());
                city->setIsTaken(true);                                                        // set a flag to true
                (*c)->getUnit()->setHasMoved();                                                // the unit that captured the city can't move or attack during this round
                (*c)->getUnit()->setHasAttacked();
            }                                                                                  // compute money of next player, add money generate by its cities to its money
            if((*c)->getBuilding() != nullptr && (*c)->getBuilding()->getOwner() == nextPlayerId)
            {
              this->players.at(nextPlayerId-1)->addPlayerMoney((*c)->getBuilding()->getMoney());
            }

            //reset flags of units of the player of the last round
            if((*c)->getUnit() != nullptr && (*c)->getUnit()->getOwner() == currentPlayerId)
            {
                (*c)->getUnit()->resetHasMoved();
                (*c)->getUnit()->resetHasAttacked();
            }
            //reset flags of cities of the palyer of the last round
            if((*c)->getBuilding() != nullptr && (*c)->getBuilding()->getOwner() == currentPlayerId)
            {
                city = dynamic_cast<City*>((*c)->getBuilding());
                city->setHasCreateUnit(false);
            }

        }
    }



    if(nextPlayerId == players.at(0)->getPlayerNumber())                                                                   // increment round
    {
        incrementTour();
    }
    this->currentPlayerId = nextPlayerId;                                                   // current player id set to next player id
    city = nullptr;
}

/*!
 * \brief Logic::getTakenCityCoords
 * \return coordinates of the cities taken by the current player
 */
vector<QPair<int, int> > Logic::getTakenCityCoords()
{
    vector<QPair<int,int>> citiesCoords;
    City* city;

    for (vector<vector<Case*>>::iterator it = logicMap.begin(); it != logicMap.end(); ++it) // for rows in logicmap
    {
        QDebug deb = qDebug().nospace();
        for (vector<Case*>::iterator c = it->begin(); c != it->end(); ++c)                  // for cases in rows
         {
            if((*c)->getBuilding() != nullptr)
            {
                city = dynamic_cast<City*>((*c)->getBuilding());
                if(city->getIsTaken())                                                  // if city is taken, add its position
                {
                    citiesCoords.push_back(qMakePair((*c)->getPosX(),(*c)->getPosY()));
                    city->setIsTaken(false);
                }
            }
        }
    }
    return citiesCoords;
}

/*!
 * \brief Logic::checkEnd
 * \return a QString, with the winner or null if not the end
 */
QString Logic::checkEnd()
{
    QString end = QString::null;
    for(Player* p : this->players)
    {
        if(p->getNbOfCity() == this->nbCities)                                  // if one player has all the cities it's the end
        {
            end = "Player "+QString::number(p->getPlayerNumber())+" won!";
            return end;
        }
    }

    if((this->currentPlayerId) % this->nbPlayers +1 == 1 && tour+1 > 100)         // if the number max of round is reach it is the end
    {
        int playerNbCity=0;
        for(Player* p : this->players)
        {
            if(p->getNbOfCity() > playerNbCity)
            {
                playerNbCity = p->getNbOfCity();
                end = "Player "+QString::number(p->getPlayerNumber());
            }
            else if(p->getNbOfCity() == playerNbCity)
            {
                end += " and " + QString::number(p->getPlayerNumber());
            }
        }
        end += " won";
        return end;
    }
    else
    {
        return end;
    }
}
