QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backup.cpp \
    defindex.cpp \
    enemyammo.cpp \
    enemyship.cpp \
    gameobj.cpp \
    gameobjpool.cpp \
    gameprop.cpp \
    main.cpp \
    playerammo.cpp \
    playership.cpp \
    qlabelgraphicsitem.cpp \
    shipammo.cpp \
    shipobj.cpp \
    widget.cpp

HEADERS += \
    defindex.h \
    enemyammo.h \
    enemyship.h \
    gameobj.h \
    gameobjpool.h \
    gameprop.h \
    playerammo.h \
    playership.h \
    qlabelgraphicsitem.h \
    shipammo.h \
    shipobj.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsrc.qrc
