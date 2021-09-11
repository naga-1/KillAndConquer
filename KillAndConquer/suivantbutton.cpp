#include "suivantbutton.h"
#include "mascene.h"
#include <QtDebug>
#include <QThread>

/*!
 * \brief SuivantButton::SuivantButton, constructor of a button named Suivant
 * \param malogic the pointer to the logic
 * \param scene the pointer to the scene
 * \param parent the pointer to the parent
 */
SuivantButton::SuivantButton(Logic *malogic, QObject *scene, QWidget *parent)
{
    setText("Tour suivant");  //We set the label
    setGeometry(476,795,275,50); //Then the geometry
    logic = malogic;
    m2 = scene;
}

/*!
 * \brief SuivantButton::~SuivantButton
 */
SuivantButton::~SuivantButton()
{

}

/*!
 * \brief SuivantButton::Action, when the button is triggered
 */
void SuivantButton::Action()
{
    logic->checkEnd();
    logic->nextPlayer();
    vector<QPair<int,int>> cityCoords = logic->getTakenCityCoords();

    int length = 50;

    MaScene* m3 = nullptr; //On initialise un nouveau pointeur de scène
    m3 = (MaScene*)m2;
    if(logic->checkEnd() != QString::null){
        m3->victoire(logic->checkEnd());
        this->setEnabled(false);
    }
    if(!cityCoords.empty())
    {
        for(QPair<int,int> coord : cityCoords){
           QString color = logic->getCityColor(coord.first*length,coord.second*length,length);// faire passer argument length à boutonsuivant ?
           if(color=="red"){
               color = "vr";
           }
           else if(color == "blue"){
               color = "vb";
           }
           else if(color == "yellow"){
               color = "vy";
           }
           else if(color == "green"){
               color = "vg";
           }
           m3->captureCity(coord.first,coord.second,color);


        }
    }


    m3->update();
}
