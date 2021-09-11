#include "maingame.h"
#include "aidebutton.h"
#include <QDebug>
#include <QtMultimedia/QAudio>
#include <QString>
#include <QSound>
#include <QtMultimedia/QMediaPlayer>
#include <QApplication>
#include <QDir>
#include <QMediaPlaylist>
#include "vect_error.h"


/*!
 * \brief mainGame::mainGame, the main class
 * \param parent
 */
mainGame::mainGame(QString filePath, int nbPlayers,QWidget *parent) : QMainWindow(parent)
{

    this->logic = new Logic(filePath, nbPlayers); //We create a new logic map thanks to the file level.txt

    //logic->readMap();

    logic->nextPlayer();                    // we start with the first player

    vue = new QGraphicsView(this); //On instancie une nouvelle vue
    scene = new MaScene(vue, logic); //On créé une nouvelle scène selon ce qui a été défini
    vue->setScene(scene); //On affecte la scène à notre vue

    vue->setFixedSize(753,848);
    vue->setAlignment(Qt::AlignLeft | Qt::AlignTop); //On aligne la vue en haut à gauche de la fenêtre
    vue->centerOn(0,0); //On centre en (0,0)
    vue->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //On enlève la scrollBar horizontale
    vue->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //On enlève la scrollBar verticale


    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("file:///" + QApplication::applicationDirPath() + "/fichiers/medieval-music-black-wolfs-inn.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);


    QMediaPlayer *player = new QMediaPlayer;
    player->setPlaylist(playlist);
    player->setVolume(10);
    player->play();

    setWindowTitle("Jeu"); //Nom de la fenêtre
    setCentralWidget(vue); //On dit que notre vue est le central widget

}

