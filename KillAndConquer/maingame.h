#ifndef MAINGAME_H
#define MAINGAME_H

#include <QMainWindow>
#include "mascene.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include "logic.h"


class mainGame : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainGame(QString filePath, int nbPlayers,QWidget *parent = nullptr);
    //MaScene *scene;



private:
    MaScene *scene;
    QGraphicsView *vue;
    Logic* logic;



};

#endif // MAINGAME_H
