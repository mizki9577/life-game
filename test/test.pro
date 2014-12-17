TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../life-game-core/

SOURCES += main.cpp \
    ../life-game-core/matrix_type.cpp

include(deployment.pri)
qtcAddDeployment()

QMAKE_CXXFLAGS += -std=c++1z

HEADERS += \
    ../life-game-core/matrix_type.hpp
