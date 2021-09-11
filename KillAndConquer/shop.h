#ifndef SHOP_H
#define SHOP_H

#include <QMainWindow>
#include <QLabel>
#include <QObject>
#include "logic.h"
#include "mascene.h"
#include <QGraphicsScene>

namespace Ui {
class Shop;
}

class Shop : public QMainWindow
{
    Q_OBJECT

public:
    explicit Shop(Logic *logic = nullptr,QObject *scene2 = Q_NULLPTR, int x = 0, int y = 0, QWidget *parent = nullptr);
    ~Shop();

private slots:
    void on_but_inf_clicked();

    void on_but_kni_clicked();

    void on_but_arc_clicked();

    void on_but_mar_clicked();

private:
    Ui::Shop *ui;
    QObject *archer;
    Logic *malogic;
    QObject* m2;
    int posX;
    int posY;
};

#endif // SHOP_H
