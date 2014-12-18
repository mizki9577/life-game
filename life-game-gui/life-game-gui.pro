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
