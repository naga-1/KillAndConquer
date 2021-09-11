#include "unitegraphique.h"
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QPalette>
#include <QtDebug>
#include "indicatorgraphics.h"
#include <QMetaObject>
#include "mascene.h"
#include <QGraphicsScene>
#include <QToolButton>
#include "windows.h"
#include <QTime>
#include <QCoreApplication>
using namespace std;

/*!
 * \brief UniteGraphique::UniteGraphique constructor of a graphic unit
 * \param type the kind of unit
 * \param scene2 the pointer of the scene
 * \param malogic the pointer to the logic
 * \param id the id of the player owner
 */
UniteGraphique::UniteGraphique(QString type, QObject *scene2, Logic *malogic, int id)
{
    QString location = ":/image/image/";
    QString color;
    QString unit;
    QString end=".png";

    if(type=="infantry")
    {
        unit ="infanterie";
    }
    else if(type=="chevalier")
    {
        unit = "chevalier";
    }
    else if(type=="archer")
    {
        unit = "archer";
    }
    else if(type=="marcher")
    {
        unit = "archerM";
    }

    setAcceptHoverEvents(true); //On dit qu'on accepte l'évennement de survole
    setRect(0,0,50,50); //On créé des cases de taille 50 par 50
    setFlag(QGraphicsItem::ItemIsMovable); //On dit que cette item est mouvable
    setFlag(QGraphicsItem::ItemIsSelectable); //Et sélectionnable
    typeUnite=type;
    m2 = scene2; //On récupère la scène sur laquelle on se trouve

    //We creat unit according to her id (it will difine her color)
    if(id==1){
        setPen(QPen(Qt::blue));
        QPixmap bkgnd(location + "blue/" + unit + end);
        bkgnd = bkgnd.scaled(50,50,Qt::IgnoreAspectRatio); //On dimentionne l'image à la taille de la fenêtre
        setBrush(bkgnd);
    }
    else if(id==2){
        setPen(QPen(Qt::red));
        QPixmap bkgnd(location + "red/" + unit + end);
        bkgnd = bkgnd.scaled(50,50,Qt::IgnoreAspectRatio); //On dimentionne l'image à la taille de la fenêtre
        setBrush(bkgnd);
    }
    else if(id==3){
        setPen(QPen(Qt::yellow));
        QPixmap bkgnd(location + "yellow/" + unit + end);
        bkgnd = bkgnd.scaled(50,50,Qt::IgnoreAspectRatio); //On dimentionne l'image à la taille de la fenêtre
        setBrush(bkgnd);
    }
    else if(id==4){
        setPen(QPen(Qt::green));
        QPixmap bkgnd(location + "green/" + unit + end);
        bkgnd = bkgnd.scaled(50,50,Qt::IgnoreAspectRatio); //On dimentionne l'image à la taille de la fenêtre
        setBrush(bkgnd);
    }
    logic = malogic; //On récupère le pointeur sur la logique
    setZValue(0);
}

/*!
 * \brief UniteGraphique::mouseReleaseEvent when the object is released to undisplay the indicators and move the unit to the right place
 * \param e
 */
void UniteGraphique::mouseReleaseEvent(QGraphicsSceneMouseEvent *e) //Méthode permettant de repositionner l'unité une fois qu'on l'a bougée
{

    if(canMove){ //If the unit can move
        int x = (pos().x() + 25 ) -((int)(pos().x() + 25 )%50); //Calcul permettant de repositionner l'unité (modulo 50 car la taille de la case est de 50 par 50)
        int y = (pos().y() + 25 ) -((int)(pos().y() + 25 )%50);
        MaScene* m3 = nullptr; //On initialise un nouveau pointeur de scène
        m3 = (MaScene*)m2; //On lui donne la valeur de la scène sur laquelle on se trouve
        tuple<int,int,int,int,int> coords; //We initialize a tuple
        coords = logic->moveUnit(valX,valY,x,y,50); //We set the values of the tuple with a logic function

        //Then we compare the first value of the tuple//
        if(get<0>(coords)==0){
            setPos(get<1>(coords)*50,get<2>(coords)*50);
        }
        else if(get<0>(coords)==1){
            m3->deleteUnit(get<3>(coords)*50,get<4>(coords)*50);
            setPos(get<1>(coords)*50,get<2>(coords)*50);

        }
        else if(get<0>(coords)==2){
            setPos(get<1>(coords)*50,get<2>(coords)*50);
            m3->deleteUnit(get<1>(coords)*50,get<2>(coords)*50);

        }
        else if(get<0>(coords)==3){
            setPos(get<1>(coords)*50,get<2>(coords)*50);
            m3->deleteUnit(get<3>(coords)*50,get<4>(coords)*50);
        }
        canHit = false;
        m3->destIndic(); //Et on appel la méthode de destruction des indicateurs
    }
    else if(!canMove && canHit){
        int x = (pos().x() + 25 ) -((int)(pos().x() + 25 )%50); //Calcul permettant de repositionner l'unité (modulo 50 car la taille de la case est de 50 par 50)
        int y = (pos().y() + 25 ) -((int)(pos().y() + 25 )%50);
        MaScene* m3 = nullptr; //On initialise un nouveau pointeur de scène
        m3 = (MaScene*)m2; //On lui donne la valeur de la scène sur laquelle on se trouve
        tuple<int,int,int,int,int> coords;
        coords = logic->moveUnit(valX,valY,x,y,50);
        if(get<0>(coords)==0){
            setPos(get<1>(coords)*50,get<2>(coords)*50);
        }
        else if(get<0>(coords)==1){
            setPos(valX,valY);
            m3->deleteUnit(get<3>(coords)*50,get<4>(coords)*50);
            setPos(get<1>(coords)*50,get<2>(coords)*50);

        }
        else if(get<0>(coords)==2){
            setPos(get<1>(coords)*50,get<2>(coords)*50);
            m3->deleteUnit(get<1>(coords)*50,get<2>(coords)*50);

        }
        else if(get<0>(coords)==3){
            setPos(valX,valY);
            m3->deleteUnit(get<3>(coords)*50,get<4>(coords)*50);
            setPos(get<1>(coords)*50,get<2>(coords)*50);
        }
        else{
           setPos(valX,valY);
        }
        m3->destIndic();
        canHit = false;

    }
    else {
        setPos(valX,valY);
    }
    QGraphicsRectItem::mouseReleaseEvent(e);
}

/*!
 * \brief UniteGraphique::mousePressEvent, display indicators where the unit is able to go or attack
 * \param e
 */
void UniteGraphique::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    MaScene* m3 = nullptr; //On initialise un nouveau pointeur de scène
    m3 = (MaScene*)m2; //On lui donne la valeur de la scène sur laquelle on se trouve
    int x = pos().x(); //On récupère les coordonnées actuelles
    int y = pos().y();
    valX = x;
    valY = y;
    if(logic->getCurrentPlayerId()==logic->getUnitOwner(x,y,50) && logic->getHasMoved(x, y, 50)){ //On vérifie que l'unité appartient au joueur actuel et que l'unité n'a pas encore bougé
       m3->indicateursDeplacement(x, y); //On appel la méthode d'affichage des indicateurs
       m3->indicateursMerge(x, y);
       m3->indicateursAttack(x, y);
       canMove = true; //On met à true la variable booléenne servant lors du relachement de l'objet à positioner coorectement ce même objet
       canHit = true;
    }
    else if(logic->getCurrentPlayerId()==logic->getUnitOwner(x,y,50) && !logic->getHasMoved(x ,y ,50) && logic->getHasAttacked(x, y, 50)) { //We only display the attack indicators
           m3->indicateursAttack(x, y);
           canHit = true;
           canMove = false;
        }
    else{
           canMove = false;
           canHit = false;
    }
    QGraphicsRectItem::mousePressEvent(e);
}

/*!
 * \brief UniteGraphique::hoverEnterEvent, allow the user to see the life of a unit when she is overed
 * \param event
 */
void UniteGraphique::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //On récupère les coordonnées de l'unité
    int x = this->pos().x();
    int y = this->pos().y();
    if(logic->isUnit(x,y,50)){ //On vérifie que nous sommes bien sur une unité
        //On récupère les données grâce à la logique
        QString hp = QString::number(logic->getUnitHP(x,y,50));
        QString hpm = QString::number(logic->getUnitMaxHP(x,y,50));
        setToolTip(hp + "/" + hpm + " HP"); //On affiche la vie actuelle sur la vie max
    }

}
