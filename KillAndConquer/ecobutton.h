#ifndef ECOBUTTON_H
#define ECOBUTTON_H

#include <QPushButton>
#include <QObject>
#include "logic.h"

class EcoButton : public QPushButton
{
    Q_OBJECT
public:
    EcoButton(Logic *malogic = nullptr, QWidget *parent = 0);
    ~EcoButton();
public slots:
    void Action();
private:
    Logic *logic;
};

#endif // ECOBUTTON_H
