#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T06:41:38
#
#-------------------------------------------------

QT       -= gui

TARGET = life-game-core
TEMPLATE = lib

DEFINES += LIFEGAMECORE_LIBRARY

SOURCES += life_game.cpp \
        matrix_type.cpp

HEADERS += life_game.hpp\
        life-game-core_global.hpp \
        matrix_type.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS += -std=c++1z
