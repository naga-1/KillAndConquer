#ifndef UNITEGRAPHIQUE_H
#define UNITEGRAPHIQUE_H

#include <QGraphicsRectItem>
#include <QObject>
//#include "mascene.h"
#include <QGraphicsScene>
#include <logic.h>

class UniteGraphique : public QGraphicsRectItem
{
public:
    UniteGraphique(QString couleur = NULL, QObject *scene2 = Q_NULLPTR, Logic *malogic = nullptr, int id = 0);
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);
    void mousePressEvent(QGraphicsSceneMouseEvent* e);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    QString typeUnite;
    QObject* m2;
private:
    Logic *logic;
    int valX;
    int valY;
    bool canMove;
    bool canHit;

};

#endif // UNITEGRAPHIQUE_H
