#include "aidebutton.h"
#include <QMessageBox>


/*!
 * \brief AideButton::AideButton
 * \param parent
 */
AideButton::AideButton(QWidget *parent):QPushButton(parent)
{
    setText("Aide");
    setGeometry(0,795,200,50);

}


AideButton::~AideButton()
{

}

/*!
 * \brief AideButton::Action, when the button is triggered we display a QMessageBox as a information
 */
void AideButton::Action()
{
    QMessageBox::information(0, "Aide","Pour jouer, cliquez sur une unité afin de la déplacer\n Vous pouvez créer des unités en cliquant sur une ville \n Vous pouvez consulter vos économies en cliquant sur 'économie' \n La dernière touche est assez explicite ...");
}
