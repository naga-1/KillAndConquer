#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QBrush>
#include <QDebug>
#include <QGraphicsView>
#include <QApplication>
#include "maingame.h"

/*!
 * \brief MainWindow::MainWindow
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Menu");
    setFixedSize(650,455); //On fixe la taille de la fenêtre
    QPixmap bkgnd(":/image/image/settings/fond.png"); //On fixe l'image de fond
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio); //On dimentionne l'image à la taille de la fenêtre
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*!
 * \brief MainWindow::on_boutonQuitter_clicked, to quit the application
 */
void MainWindow::on_boutonQuitter_clicked()
{
    QApplication::quit();
}

/*!
 * \brief MainWindow::on_boutonJouer_clicked, to start a new game
 */
void MainWindow::on_boutonJouer_clicked()
{
    mainGame * jeu= new mainGame(":/fichiers/fichiers/level.txt",3);
    jeu->show();
    this->hide();
}
