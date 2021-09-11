#include "joueur.h"
#include <QLabel>
#include <QBrush>
#include <QPalette>
#include <QString>
#include <QtDebug>

joueur::joueur(Logic *logic, int id)
{
    //int a = logic->getCurrentPlayerId();
    QString nbr = QString::number(id+1);
    QString text1 = {"Joueur "};
    QString text = text1 + nbr;
    setText(text);
    QFont f( "Arial", 30, QFont::Bold);
    setFont(f);
    //setBrush(QBrush(Qt::green));
    setGeometry(100,100,300,80);
    //logic = malogic;
}

void joueur::update(int id)
{
    qDebug() << "Update" << endl;
    QString nbr = QString::number(id+1);
    QString text1 = {"Joueur "};
    QString text = text1 + nbr;
    setText(text);
    QFont f( "Arial", 30, QFont::Bold);
    setFont(f);
    //setGeometry(100,100,300,80);
}
