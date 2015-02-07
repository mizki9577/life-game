TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

QMAKE_CXXFLAGS += -std=c++1z

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../life-game-core/release/ -llife-game-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../life-game-core/debug/ -llife-game-core
else:unix: LIBS += -L$$OUT_PWD/../life-game-core/ -llife-game-core

INCLUDEPATH += $$PWD/../life-game-core
DEPENDPATH += $$PWD/../life-game-core
