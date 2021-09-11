#ifndef AFFICHAGEECO_H
#define AFFICHAGEECO_H

#include <QMainWindow>
#include "logic.h"

namespace Ui {
class AffichageEco;
}

class AffichageEco : public QMainWindow
{
    Q_OBJECT

public:
    explicit AffichageEco(Logic *malogic = nullptr, QWidget *parent = nullptr);
    ~AffichageEco();

private:
    Ui::AffichageEco *ui;
};

#endif // AFFICHAGEECO_H
