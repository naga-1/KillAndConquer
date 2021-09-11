#include "mascene.h"
#include "cases.h"
#include "unitegraphique.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <vector>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "indicatorgraphics.h"
#include <QLabel>
#include <QLayout>
#include <QPointF>
#include <QTransform>
#include <QThread>

using namespace std;

/*!
 * \brief MaScene::MaScene, the scene thzt will be used for the vue
 * \param parent
 * \param malogic the pointer to the logic
 */
MaScene::MaScene(QObject *parent, Logic *malogic) : QGraphicsScene(parent)
{
    QFile fichier(malogic->getFilePath()); //On ouvre notre fichier texte contenant le niveau
    int x = 0;
    int y = 0;
    listeMots = new vector<QString>; //On initialise une liste de mots qui correspondra aux lettres du fichier
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);
        while(!flux.atEnd())
        {
            QString temp = flux.readLine(); //On lit le fichier ligne par ligne
            x += 1; //On incrémente x pour connaitre les dimmentions du tableau
            QTextStream ligne(&temp);
            QString mot;
            y = 0;
            while(! ligne.atEnd()) //On lit chaque ligne mot par mot que nous allons ajouter à notre liste de mots
            {
                ligne >> mot;
                y += 1; //On incrémente y pour connaitre la largeur de la fenêtre
                listeMots->push_back(mot);
            }
        }
        fichier.close();
    }
    int k = 0;
    for(int i = 0; i < x;i++){
            for(int j = 0; j < y; j++){
                Cases* item = new Cases(listeMots->at(k), malogic, this); //On créé une nouvelle case
                item->setPos(j*50, i*50); //On fixe sa position
                addItem(item); //On ajoute le nouvel item à la scène
                k += 1;
            }
        }
    listeMots->clear();
    delete listeMots;

    //Label numéro joueur//
    labelJoueur = new QLabel();
    labelJoueur->setGeometry(0,751,800,45);
    QString nbr = QString::number(1);
    QString text1 = {"  Joueur "};
    QString text = text1 + nbr;
    labelJoueur->setText(text);
    QFont f( "Arial", 30, QFont::Bold);
    labelJoueur->setStyleSheet("QLabel {color : blue; }");
    labelJoueur->setFont(f);
    QGraphicsProxyWidget *proxy4 = new QGraphicsProxyWidget();
    proxy4->setWidget(labelJoueur);
    addItem(proxy4);

    //Label numéro tour//
    labelTour = new QLabel();
    labelTour->setGeometry(580,751,800,45);
    QString nbr2 = QString::number(1);
    QString text2 = {"Tour "};
    QString texte = text2 + nbr2;
    labelTour->setText(texte);
    labelTour->setFont(f);
    QGraphicsProxyWidget *proxy5 = new QGraphicsProxyWidget();
    proxy5->setWidget(labelTour);
    addItem(proxy5);

    //Bouton aide
    aide = new AideButton();
    connect(aide, SIGNAL(clicked(bool)), aide, SLOT(Action())); //On connect un slot pour détecter l'évènement
    mes_btn.append(aide);
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
    proxy->setWidget(aide);
    addItem(proxy);

    //Bouton economie
    economie = new EcoButton(malogic);
    connect(economie, SIGNAL(clicked(bool)), economie, SLOT(Action()));
    QGraphicsProxyWidget *proxy2 = new QGraphicsProxyWidget();
    proxy2->setWidget(economie);
    addItem(proxy2);
    mes_btn.append(economie);

    //Bouton suivant
    suivant = new SuivantButton(malogic, this);
    connect(suivant, SIGNAL(clicked(bool)), suivant, SLOT(Action()));
    QGraphicsProxyWidget *proxy3 = new QGraphicsProxyWidget();
    proxy3->setWidget(suivant);
    addItem(proxy3);
    mes_btn.append(suivant);

    //Logic
    logic = malogic;



}

/*!
 * \brief MaScene::indicateursDeplacement, indicators that will be displayed to see where the unit can go
 * \param x the x coordinate of the unit
 * \param y the y coordinate of the unit
 */
void MaScene::indicateursDeplacement(int x, int y)
{
    vector<QPair<int, int>> coords; //We create a vector for the coordinates
    coords = logic->getUnitMoveCoords(x, y, 50); //That we get from the logic

    if (coords.empty()){

     }
     else {
         for (vector<QPair<int,int>>::iterator coord = coords.begin(); coord != coords.end(); ++coord){
             IndicatorGraphics* item = new IndicatorGraphics("blue"); //On créé un nouvel indicateur
             item->setPos((*coord).first*(50)+20,(*coord).second*(50)+20); //On fixe sa position
             addItem(item); //We add the item to the scene
             mes_indic.append(item);
         }
    }
}

/*!
 * \brief MaScene::indicateursDeplacement, indicators that will be displayed to see where the unit can merge with another one
 * \param x the x coordinate of the unit
 * \param y the y coordinate of the unit
 */
void MaScene::indicateursMerge(int x, int y)
{
    vector<QPair<int, int>> coords; //We create a vector for the coordinates
    coords = logic->getUnitMergeCoords(x, y, 50); //That we get from the logic

    if (coords.empty()){

     }
     else {
         for (vector<QPair<int,int>>::iterator coord = coords.begin(); coord != coords.end(); ++coord){
             IndicatorGraphics* item = new IndicatorGraphics("green"); //On créé un nouvel indicateur
             item->setPos((*coord).first*(50)+20,(*coord).second*(50)+20); //On fixe sa position
             addItem(item); //We add the item to the scene
             mes_indic.append(item);
         }
    }
}

/*!
 * \brief MaScene::indicateursAttack, indicators that will be displayed to know if the unit can attack another ennemy
 * \param x the x coordinate of the unit
 * \param y the y coordinate of the unit
 */
void MaScene::indicateursAttack(int x, int y)
{
    /*for (vector<QPair<int,int>>::iterator coord = attackCoords.begin(); coord != attackCoords.end(); ++coord)
            {
                if((*coord).first == X2 && (*coord).second == Y2)*/
    vector<QPair<int, int>> coords2; //We create a vector for the coordinates
    coords2 = logic->getUnitAttackCoords(x, y, 50); //That we get from the logic
    if (coords2.empty()){

     }
    else{
        for (vector<QPair<int,int>>::iterator coord = coords2.begin(); coord != coords2.end(); ++coord){
            IndicatorGraphics* item = new IndicatorGraphics("red"); //On créé un nouvel indicateur
            item->setPos((*coord).first*(50)+20,(*coord).second*(50)+20); //On fixe sa position
            addItem(item);
            mes_indic.append(item);
        }
    }

}

/*!
 * \brief MaScene::destIndic, to destroy the differents indicators
 */
void MaScene::destIndic()
{
    if(!mes_indic.empty()){
        for(int i = mes_indic.size()-1; i !=0 ; i-- ){ //On détruit les cases une par une
                removeItem(mes_indic.at(i));
                mes_indic.removeAt(i);
        }
        removeItem(mes_indic.at(0));
        mes_indic.removeAt(0);
    }

}

/*!
 * \brief MaScene::createUnit, to create a new unit
 * \param x the x coordinate of the unit
 * \param y the y coordinate of the unit
 * \param type the kind of unit
 */
void MaScene::createUnit(int x, int y, QString type)
{
    if(type == "infantry"){
        int id = logic->getCurrentPlayerId();
        UniteGraphique* item = new UniteGraphique(type, this, logic, id); //On créé une nouvelle case
        item->setPos(x,y); //On fixe sa position
        addItem(item);
    }
    else if(type == "chevalier"){
        int id = logic->getCurrentPlayerId();
        UniteGraphique* item = new UniteGraphique(type, this, logic, id); //On créé une nouvelle case
        item->setPos(x,y); //On fixe sa position
        addItem(item);
    }
    else if(type == "archer"){
        int id = logic->getCurrentPlayerId();
        UniteGraphique* item = new UniteGraphique(type, this, logic, id); //On créé une nouvelle case
        item->setPos(x,y); //On fixe sa position
        addItem(item);
    }
    else if(type == "marcher"){
        int id = logic->getCurrentPlayerId();
        UniteGraphique* item = new UniteGraphique(type, this, logic, id); //On créé une nouvelle case
        item->setPos(x,y); //On fixe sa position
        addItem(item);
    }
}

/*!
 * \brief MaScene::update, to update the currend player number and the turn
 */
void MaScene::update()
{
    int id = logic->getCurrentPlayerId(); //We get the player id
    QString nbr = QString::number(id); //Taht we cast in QString
    QString text1 = {"  Joueur "};
    QString text = text1 + nbr;
    labelJoueur->setText(text); //And we set the final text
    QFont f( "Arial", 30, QFont::Bold);

    //We change the color of the text according to the player id
    if(id == 1){
        labelJoueur->setStyleSheet("QLabel {color : blue; }");
    }
    else if(id == 2){
        labelJoueur->setStyleSheet("QLabel {color : red; }");
    }
    else if(id == 3){
        labelJoueur->setStyleSheet("QLabel {color : yellow; }");
    }
    else if(id == 4){
        labelJoueur->setStyleSheet("QLabel {color : green; }");
    }
    labelJoueur->setFont(f);

    //We do the same thing for the current turn number
    int tour = logic->getTour();
    QString nbr2 = QString::number(tour);
    QString text2 = {"Tour "};
    QString texte = text2 + nbr2;
    labelTour->setText(texte);
    labelTour->setFont(f);
}

/*!
 * \brief MaScene::deleteUnit, to delete a unit
 * \param x the x coordinate of the unit
 * \param y the y coordinate of the unit
 */
void MaScene::deleteUnit(int x, int y)
{
    QGraphicsItem* item;
    qreal x2 = x;
    qreal y2 = y;
    item = itemAt(x2 , y2, QTransform()); //We get the unit thanks to the coordinates
    removeItem(item); //And we remove it from the scene
}

void MaScene::captureCity(int x, int y, QString color)
{
    QGraphicsItem* item;
    qreal x2 = x*50;
    qreal y2 = y*50;
    item = itemAt(x2 , y2, QTransform()); //We get the unit thanks to the coordinates
    item ->setPos(-1,-1); //And we remove it from the scene
    item = itemAt(x2 , y2, QTransform());
    removeItem(item);
    Cases* item2 = new Cases(color, logic, this);
    item2 -> setPos(x2,y2);
    addItem(item2);
    item = itemAt(-1 , -1, QTransform());
    item -> setPos(x2,y2);

}

/*!
 * \brief MaScene::victoire, display the end message
 * \param text
 */
void MaScene::victoire(QString text)
{
    int taille = text.length();

    if(taille>20){
        victory = new QLabel();
        victory->setGeometry(190,757,200,20);
        victory->setText(text);
        QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
        proxy->setWidget(victory);
        addItem(proxy);
        QFont f( "Arial", 23, QFont::Bold);
        victory->setStyleSheet("QLabel {color : #FB8D01; }");
        victory->setFont(f);
    }
    else if(taille<15){
        victory = new QLabel();
        victory->setGeometry(250,751,200,20);
        victory->setText(text);
        QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
        proxy->setWidget(victory);
        addItem(proxy);
        QFont f( "Arial", 29, QFont::Bold);
        victory->setStyleSheet("QLabel {color : #FB8D01; }");
        victory->setFont(f);
    }
    else{
        victory = new QLabel();
        victory->setGeometry(192,751,200,20);
        victory->setText(text);
        QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
        proxy->setWidget(victory);
        addItem(proxy);
        QFont f( "Arial", 29, QFont::Bold);
        victory->setStyleSheet("QLabel {color : #FB8D01; }");
        victory->setFont(f);
    }


}




MaScene::~MaScene(){

    for(int i = 0; mes_btn.size(); i++ ){ //On détruit les cases une par une
        delete mes_btn.at(i);

    }


}


