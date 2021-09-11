#ifndef JOUEUR_H
#define JOUEUR_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include "logic.h"

class joueur : public QLabel
{
public:
    joueur(Logic *logic, int id);
    void update(int id);
};

#endif // JOUEUR_H
