#include "indicatorgraphics.h"
#include <QBrush>
#include <QPen>

QColor* IndicatorGraphics::moveColor = new QColor(124,185,232);
QColor* IndicatorGraphics::attackColor = new QColor(255,126,0);
QColor* IndicatorGraphics::mergeColor = new QColor(0,204,102);

/*!
 * \brief IndicatorGraphics::IndicatorGraphics, constructor of indicators
 * \param couleur
 */
IndicatorGraphics::IndicatorGraphics(QString couleur)
{
    setZValue(1);
    //We set different colors according to the QString "couleur"
    if(couleur == "blue"){
        setRect(QRectF(0, 0, 10, 10));

        QPen pen(*moveColor);
        setPen(QPen(pen));

        QBrush brush(*moveColor);
        setBrush(QBrush(brush));
    }
    else if(couleur == "red"){
        setRect(QRectF(0, 0, 10, 10));

        QPen pen(*attackColor);
        setPen(QPen(pen));

        QBrush brush(*attackColor);
        setBrush(QBrush(brush));
    }
    else if(couleur == "green"){
        setRect(QRectF(0, 0, 10, 10));

        QPen pen(*mergeColor);
        setPen(QPen(pen));

        QBrush brush(*mergeColor);
        setBrush(QBrush(brush));
    }
}
