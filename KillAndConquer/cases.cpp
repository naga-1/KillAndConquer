#include "cases.h"
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QPalette>
#include "shop.h"
#include <QDebug>
#include "vect_error.h"


/*!
 * \brief Cases::Cases, constructor of the cases of the scene
 * \param couleur the kind of case we want to create
 * \param logic the pointer to the logic
 * \param scene2 the pointer to the scene
 */
Cases::Cases(QString couleur, Logic *logic, QObject *scene2)
{
    malogic = logic;
    m2=scene2;
    setZValue(-1);
    if(couleur=="g"){
        setRect(0,0,length,length); //On créé des cases de taille 50 par 50
        setPen(QPen(Qt::black));
        setBrush(QBrush(Qt::green));
    }
    else if(couleur=="w"){
        setRect(0,0,length,length); //On créé des cases de taille 50 par 50
        setPen(QPen(Qt::black));
        setBrush(QBrush(Qt::blue));

        QPixmap bkgnd(":/image/image/case/sea2.png");
        setBrush(bkgnd);
    }
    else if(couleur=="f"){

        setRect(0,0,length,length); //On créé des cases de taille 50 par 50
        setPen(QPen(Qt::black));
        setBrush(QBrush(Qt::darkGreen));

        QPixmap bkgnd(":/image/image/case/tree2.png");
        setBrush(bkgnd);


    }
    else if(couleur=="m"){
        setRect(0,0,length,length); //On créé des cases de taille 50 par 50
        setPen(QPen(Qt::black));
        setBrush(QBrush(Qt::gray));

        QPixmap bkgnd(":/image/image/case/mountains2.png");
        setBrush(bkgnd);
    }
    else if(couleur=="vb"){
        setRect(0,0,length,length); //On créé des cases de taille 50 par 50
        setPen(QPen(Qt::black));
        setBrush(QBrush(Qt::green));
        setFlag(QGraphicsItem::ItemIsSelectable);
        QPixmap bkgnd(":/image/image/blue/castle.png");
        bkgnd = bkgnd.scaled(length,length,Qt::IgnoreAspectRatio); //On dimentionne l'image à la taille de la fenêtre
        setBrush(bkgnd);
    }
    else if(couleur=="vr"){
        setRect(0,0,length,length); //On créé des cases de taille 50 par 50
        setPen(QPen(Qt::black));
        setBrush(QBrush(Qt::green));
        setFlag(QGraphicsItem::ItemIsSelectable);
        QPixmap bkgnd(":/image/image/red/castle.png");
        bkgnd = bkgnd.scaled(length,length,Qt::IgnoreAspectRatio); //On dimentionne l'image à la taille de la fenêtre
        setBrush(bkgnd);
    }
    else if(couleur=="vy"){
        setRect(0,0,length,length); //On créé des cases de taille 50 par 50
        setPen(QPen(Qt::black));
        setBrush(QBrush(Qt::green));
        setFlag(QGraphicsItem::ItemIsSelectable);
        QPixmap bkgnd(":/image/image/yellow/castle.png");
        bkgnd = bkgnd.scaled(length,length,Qt::IgnoreAspectRatio); //On dimentionne l'image à la taille de la fenêtre
        setBrush(bkgnd);
    }
    else if(couleur=="vg"){
        setRect(0,0,length,length); //On créé des cases de taille 50 par 50
        setPen(QPen(Qt::black));
        setBrush(QBrush(Qt::green));
        setFlag(QGraphicsItem::ItemIsSelectable);
        QPixmap bkgnd(":/image/image/green/castle.png");
        bkgnd = bkgnd.scaled(length,length,Qt::IgnoreAspectRatio); //On dimentionne l'image à la taille de la fenêtre
        setBrush(bkgnd);
    }
    else if(couleur=="v"){
        setRect(0,0,length,length); //On créé des cases de taille 50 par 50
        setPen(QPen(Qt::black));
        setBrush(QBrush(Qt::green));
        setFlag(QGraphicsItem::ItemIsSelectable);
        QPixmap bkgnd(":/image/image/neutral/castle.png");
        bkgnd = bkgnd.scaled(length,length,Qt::IgnoreAspectRatio); //On dimentionne l'image à la taille de la fenêtre
        setBrush(bkgnd);
    }

}

/*!
 * \brief Cases::mousePressEvent, when the object cases is triggered (it can be a city) we display the shop if the conditions allows it
 * \param e
 */
void Cases::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    int x = pos().x();
    int y = pos().y();

    try // try catch, if getCityOwner send errors we catch them (e.i stl vector error or city on case can't be reach)
    {
        if(malogic->getCityOwner(x, y, length)==malogic->getCurrentPlayerId()){ //We check if the city is to the player who is currently playing
            bool canCreat = malogic->canCreate(x, y, 50); //We check if the city can creat a unit
            if(canCreat){
                Shop * jeu= new Shop(malogic, m2, x, y);
                jeu->show();
            }

        }
        QGraphicsRectItem::mousePressEvent(e);

    }
    catch (const exception &e)
    {
        //qDebug()<<e.what();
    }
    catch (vect_error a)
    {
        //qDebug()<<a.error;
    }

}
