#include "shop.h"
#include "ui_shop.h"
#include <QPixmap>
#include <QDebug>
#include <QPushButton>
#include <QBrush>
#include <QString>
#include <QDebug>
#include <QFont>

/*!
 * \brief Shop::Shop, constructor of the shop window
 * \param logic the pointer to the logic
 * \param scene2 the pointer to the scene
 * \param x the x coordinate of the city
 * \param y the y coordinate of the city
 * \param parent
 */
Shop::Shop(Logic *logic, QObject *scene2, int x, int y, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Shop)
{
    ui->setupUi(this);
    setWindowTitle("Shop");
    setWindowModality(Qt::ApplicationModal); //When we launch the window, the rest of the application is unusable
    setFixedSize(930,554); //On fixe la taille de la fenêtre
    QPixmap bkgnd(":/image/image/settings/img_shop.jpg"); //On fixe l'image de fond
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio); //On dimentionne l'image à la taille de la fenêtre
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //On met des icones correspondant à chaque unité dans des QPushButton

    ui->but_inf->setFlat(true); //On enlève l'aspect de base du bouton
    ui->but_inf->setIcon(QIcon(":/image/image/settings/infanterie_shop.png")); //On donne l'adresse de l'image qui servira d'icone
    ui->but_inf->setFixedSize(256,256); //On défini la taille du bouton
    ui->but_inf->setIconSize(QSize(256,256)); //Et la taille de l'icone
    ui->but_kni->setFlat(true);
    ui->but_kni->setIcon(QIcon(":/image/image/settings/chevalier_shop.png"));
    ui->but_kni->setFixedSize(256,256);
    ui->but_kni->setIconSize(QSize(256,256));
    ui->but_arc->setFlat(true);
    ui->but_arc->setIcon(QIcon(":/image/image/settings/archer_shop.png"));
    ui->but_arc->setFixedSize(256,256);
    ui->but_arc->setIconSize(QSize(256,256));
    ui->but_mar->setFlat(true);
    ui->but_mar->setIcon(QIcon(":/image/image/settings/archerM_shop.png"));
    ui->but_mar->setFixedSize(256,256);
    ui->but_mar->setIconSize(QSize(256,256));
    malogic = logic;

    int argent = malogic->getCurrentPlayerEco(); //We get the money from the logic
    ui->Eco->setText(QString::number(argent)); //And we display it
    QFont f( "Arial", 18, QFont::Bold);
    ui->Eco->setStyleSheet("QLabel {color : white; }");
    ui->Eco->setFont(f);
    QPixmap mon(":/image/image/settings/monnaie.png");
    mon.scaled(28,28);
    ui->argent->setPixmap(mon);
    m2=scene2;
    posX=x;
    posY=y;
}

Shop::~Shop()
{
    delete ui;
}

//Slots correspondant aux boutons pour acheter une unité
/*!
 * \brief Shop::on_but_inf_clicked, to buy an infantry
 */
void Shop::on_but_inf_clicked()
{
    if(malogic->getCurrentPlayerEco()>=malogic->getCostUnit(1)){
         MaScene* m3 = nullptr; //On initialise un nouveau pointeur de scène
        m3 = (MaScene*)m2;
        m3->createUnit(posX,posY,"infantry");
        malogic->createUnit(posX,posY,50,malogic->getCurrentPlayerId(),1);
        this->close();
    }

}

/*!
 * \brief Shop::on_but_kni_clicked, to buy a knight
 */
void Shop::on_but_kni_clicked()
{
    if(malogic->getCurrentPlayerEco()>=malogic->getCostUnit(2)){
        MaScene* m3 = nullptr; //On initialise un nouveau pointeur de scène
        m3 = (MaScene*)m2;
        m3->createUnit(posX,posY,"chevalier");
        malogic->createUnit(posX,posY,50,malogic->getCurrentPlayerId(),2);
        this->close();
    }
}

/*!
 * \brief Shop::on_but_arc_clicked, to buy an archer
 */
void Shop::on_but_arc_clicked()
{
    if(malogic->getCurrentPlayerEco()>=malogic->getCostUnit(3)){
        MaScene* m3 = nullptr; //On initialise un nouveau pointeur de scène
        m3 = (MaScene*)m2;
        m3->createUnit(posX,posY,"archer");
        malogic->createUnit(posX,posY,50,malogic->getCurrentPlayerId(),3);
        this->close();
    }
}


/*!
 * \brief Shop::on_but_mar_clicked, to buy a mounted archer
 */
void Shop::on_but_mar_clicked()
{
    if(malogic->getCurrentPlayerEco()>=malogic->getCostUnit(4)){
        MaScene* m3 = nullptr; //On initialise un nouveau pointeur de scène
        m3 = (MaScene*)m2;
        m3->createUnit(posX,posY,"marcher");
        malogic->createUnit(posX,posY,50,malogic->getCurrentPlayerId(),4);
        this->close();
    }
}
