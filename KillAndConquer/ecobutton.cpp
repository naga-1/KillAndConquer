#include "ecobutton.h"
#include <QMessageBox>
#include "affichageeco.h"

/*!
 * \brief EcoButton::EcoButton, constructor of the economie button
 * \param malogic
 * \param parent
 */
EcoButton::EcoButton(Logic *malogic, QWidget *parent)
{
    setText("Economie");
    setGeometry(201,795,275,50);
    logic = malogic;
}

EcoButton::~EcoButton()
{

}

/*!
 * \brief EcoButton::Action, display a new window when the button is triggered
 */
void EcoButton::Action()
{
    AffichageEco * jeu= new AffichageEco(logic);

    jeu->show();
}
