QT = core
QT += testlib
CONFIG += testcase
CONFIG += c++20 cmdline

ACTARIA_PATH = $$PWD/../

DEFAULT_ENGINE_VERSION_PATH = $$ACTARIA_PATH/include/Entities/Versions/Act_1_0

ALIASES = $$ACTARIA_PATH/include/Aliases

INCLUDEPATH += $$ACTARIA_PATH/include/
INCLUDEPATH += $$ACTARIA_PATH/include/Aliases
INCLUDEPATH += $$ACTARIA_PATH/include/Entities
INCLUDEPATH += $$ACTARIA_PATH/include/Compiler
INCLUDEPATH += $$ACTARIA_PATH/include/GUI
INCLUDEPATH += $$ACTARIA_PATH/include/VM
INCLUDEPATH += $$DEFAULT_ENGINE_VERSION_PATH

SOURCES += $$files($$ACTARIA_PATH/src/Entities/*.cpp)
SOURCES += $$files($$ACTARIA_PATH/src/Compiler/*.cpp)
SOURCES += $$files($$ACTARIA_PATH/src/VM/*.cpp)
SOURCES += $$files($$PWD/*.cpp)
SOURCES += $$files($$ACTARIA_PATH/src/*.cpp)

SOURCES -= $$ACTARIA_PATH/src/main.cpp
DEFINES += ACTARIA_TEST

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    enginetest.h \
    testutils.h
