#ifndef INDICATORGRAPHICS_H
#define INDICATORGRAPHICS_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QColor>

class IndicatorGraphics : public QGraphicsEllipseItem
{
private:
    static QColor* moveColor;
    static QColor* attackColor;
    static QColor* mergeColor;
public:
    IndicatorGraphics(QString couleur = "red");
};

#endif // INDICATORGRAPHICS_H
