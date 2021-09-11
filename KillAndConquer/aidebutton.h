#ifndef AIDEBUTTON_H
#define AIDEBUTTON_H

#include <QPushButton>
#include <QObject>
#include <QPushButton>

class AideButton : public QPushButton
{
    Q_OBJECT
public:
    AideButton(QWidget *parent = 0);
    ~AideButton();
public slots:
    void Action();
};

#endif // AIDEBUTTON_H
