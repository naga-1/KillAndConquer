#ifndef CASES_H
#define CASES_H

#include <QGraphicsRectItem>
#include "logic.h"
#include "mascene.h"
#include <QGraphicsScene>

class Cases : public QGraphicsRectItem
{
public:
    Cases(QString couleur = NULL, Logic *logic = nullptr, QObject *scene2 = Q_NULLPTR);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* e);

private:
    Logic *malogic;
    int length = 50;
    QObject* m2;
};

#endif // CASES_H
