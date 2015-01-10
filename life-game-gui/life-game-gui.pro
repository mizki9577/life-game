#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T17:30:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = life-game-gui
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.hpp

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++1z

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../life-game-core/release/ -llife-game-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../life-game-core/debug/ -llife-game-core
else:unix: LIBS += -L$$OUT_PWD/../life-game-core/ -llife-game-core

INCLUDEPATH += $$PWD/../life-game-core
DEPENDPATH += $$PWD/../life-game-core
