#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T17:30:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = life-game-gui
TEMPLATE = app

INCLUDEPATH += ../life-game-core/

SOURCES += main.cpp\
        mainwindow.cpp \
    ../life-game-core/life_game.cpp \
    ../life-game-core/matrix_type.cpp

HEADERS  += mainwindow.hpp \
    ../life-game-core/life_game.hpp \
    ../life-game-core/matrix_type.hpp

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++1z
