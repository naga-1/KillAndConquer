#include "affichageeco.h"
#include "ui_affichageeco.h"

/*!
 * \brief AffichageEco::AffichageEco, constructor of the window who display the currend player economie
 * \param malogic the pointer to the logic
 * \param parent
 */
AffichageEco::AffichageEco(Logic *malogic, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AffichageEco)
{
    ui->setupUi(this);
    setWindowTitle("Economie");
    setWindowModality(Qt::ApplicationModal);
    setFixedSize(360,100); //On fixe la taille de la fenêtre
    QPixmap bkgnd(":/image/image/settings/img_shop.jpg"); //On fixe l'image de fond
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio); //On dimentionne l'image à la taille de la fenêtre
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    QPixmap mon(":/image/image/settings/monnaie.png");
    ui->icon_argent->setPixmap(mon);

    int argent = malogic->getCurrentPlayerEco(); //We get the economie from the logic
    ui->argent->setText(QString::number(argent));
    QFont f( "Arial", 18, QFont::Bold);
    ui->argent->setStyleSheet("QLabel {color : white; }");
    ui->argent->setFont(f);
}

AffichageEco::~AffichageEco()
{
    delete ui;
}
