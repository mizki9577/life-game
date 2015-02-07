TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

QMAKE_CXXFLAGS += -std=c++1z

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../life-game-core2/release/ -llife-game-core2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../life-game-core2/debug/ -llife-game-core2
else:unix: LIBS += -L$$OUT_PWD/../life-game-core2/ -llife-game-core2

INCLUDEPATH += $$PWD/../life-game-core2
DEPENDPATH += $$PWD/../life-game-core2
