QT       += \
            core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    affichageeco.cpp \
    aidebutton.cpp \
    archer.cpp \
    building.cpp \
    case.cpp \
    cases.cpp \
    city.cpp \
    ecobutton.cpp \
    entity.cpp \
    forest.cpp \
    grass.cpp \
    indicatorgraphics.cpp \
    infantry.cpp \
    knight.cpp \
    logic.cpp \
    main.cpp \
    maingame.cpp \
    mainwindow.cpp \
    mascene.cpp \
    mountain.cpp \
    mountedarcher.cpp \
    player.cpp \
    shop.cpp \
    suivantbutton.cpp \
    unitegraphique.cpp \
    unit.cpp \
    vect_error.cpp \
    water.cpp

HEADERS += \
    affichageeco.h \
    archer.h \
    case.h \
    city.h \
    building.h \
    entity.h \
    cases.h \
    forest.h \
    grass.h \
    infantry.h \
    knight.h \
    aidebutton.h \
    ecobutton.h \
    entity.h \
    cases.h \
    indicatorgraphics.h \
    logic.h \
    maingame.h \
    mainwindow.h \
    mascene.h \
    mountain.h \
    mountedarcher.h \
    player.h \
    shop.h \
    suivantbutton.h \
    unitegraphique.h \
    unit.h \
    vect_error.h \
    water.h

FORMS += \
    affichageeco.ui \
    mainwindow.ui \
    shop.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Ressources.qrc

DISTFILES += \
    KillAndConquer.pro.user \


