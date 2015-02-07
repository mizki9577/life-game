TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    matrix_type.cpp \
    life_game.cpp

include(deployment.pri)
qtcAddDeployment()

QMAKE_CXXFLAGS += -std=c++1z

HEADERS += \
    matrix_type.hpp \
    life_game.hpp
