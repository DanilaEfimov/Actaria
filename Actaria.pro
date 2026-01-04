QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

DEFAULT_ENGINE_VERSION_PATH = include/Entities/Versions/Act_1_0
ALIASES = include/Aliases

INCLUDEPATH += include \
            include/Aliases \
            $$DEFAULT_ENGINE_VERSION_PATH \
            $$ALIASES

SOURCES += $$files(src/Entities/*.cpp) \
           $$files(include/Entities/Operators/*.cpp) \
           $$files(src/GUI/*.cpp) \
           $$files(src/*.cpp) \
           src/Entities/Operators/operator.cpp

HEADERS += $$files(include/Entities/*.h) \
           $$files(include/Entities/Operators/*.h) \
           $$files(include/GUI/*.h) \
           $$files(include/Aliases/*.h) \
           $$files($$DEFAULT_ENGINE_VERSION_PATH/*.ser) \
           $$files(include/*.h) \
           include/Entities/Operators/operator.h

FORMS += \
    mainwindow.ui

DEFINES += PRE_ORDER

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    abi \
    api \
    include/Entities/Versions/Act_1_0/operator.ser \
    target
