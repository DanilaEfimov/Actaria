QT = core testlib

CONFIG += testcase c++20 cmdline

ACTARIA_PATH = $$PWD/../

LIBS += -L$$ACTARIA_PATH/build/ -lactariacore

DEFAULT_ENGINE_VERSION_PATH = $$ACTARIA_PATH/include/Entities/Versions/Act_1_0
ALIASES = $$ACTARIA_PATH/include/Aliases

INCLUDEPATH += $$ACTARIA_PATH/include
INCLUDEPATH += $$DEFAULT_ENGINE_VERSION_PATH
INCLUDEPATH += $$ALIASES

HEADERS += globals.h \
           enginetest.h \
           testutils.h

SOURCES += $$files($$PWD/*.cpp)

DEFINES += ACTARIA_TEST

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:LIBS += -L$$ACTARIA_PATH/build/debug -lactariacore
unix:LIBS += -L$$ACTARIA_PATH/build/debug -lactariacore

INCLUDEPATH += $$PWD/../build
DEPENDPATH += $$PWD/../build

