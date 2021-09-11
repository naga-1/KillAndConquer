#ifndef MASCENE_H
#define MASCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QWidget>
#include <QLabel>

#include <vector>
#include <QPushButton>
#include "aidebutton.h"
#include "suivantbutton.h"
#include "ecobutton.h"
#include "unitegraphique.h"
#include <QGraphicsEllipseItem>
#include "logic.h"
#include "cases.h"
using namespace std;

class MaScene : public QGraphicsScene
{
public:
    MaScene(QObject *parent = Q_NULLPTR, Logic *malogic = nullptr);
    ~MaScene();
    void indicateursDeplacement(int x = 0, int y = 0);
    void indicateursMerge(int x = 0, int y = 0);
    void indicateursAttack(int x = 0, int y = 0);
    void destIndic();
    void createUnit(int x, int y, QString type);
    void update();
    void deleteUnit(int x, int y);
    void captureCity(int x, int y, QString color);
    void victoire(QString text);



private:
    QList<QPushButton*> mes_btn;
    QList<QGraphicsEllipseItem*> mes_indic;
    vector<QString>* listeMots;
    AideButton* aide;
    EcoButton* economie;
    SuivantButton* suivant;
    Logic *logic;
    QLabel *labelJoueur;
    QLabel *labelTour;
    QLabel *victory;

};

#endif // MASCENE_H
