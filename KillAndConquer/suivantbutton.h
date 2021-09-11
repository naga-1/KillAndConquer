#ifndef SUIVANTBUTTON_H
#define SUIVANTBUTTON_H

#include <QPushButton>
#include <QObject>
#include "logic.h"

class SuivantButton : public QPushButton
{
    Q_OBJECT
public:
    SuivantButton(Logic *malogic = nullptr,QObject *scene = nullptr, QWidget *parent = 0 );
    ~SuivantButton();
private:
    Logic *logic;
    QObject* m2;
public slots:
    void Action();

};

#endif // SUIVANTBUTTON_H
