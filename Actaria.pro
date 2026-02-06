QT += core

TARGET = actariacore
TEMPLATE = lib
CONFIG += staticlib c++20

DEFAULT_ENGINE_VERSION_PATH = include/Entities/Versions/Act_1_0
ALIASES = include/Aliases

INCLUDEPATH += include \
            $$DEFAULT_ENGINE_VERSION_PATH \
            $$ALIASES

SOURCES += $$files(src/Entities/*.cpp) \
           $$files(src/Entities/Operators/*.cpp) \
           $$files(src/Errors/*.cpp) \
           $$files(src/Logging/*.cpp) \
           src/stringlistcursor.cpp \
           src/utils.cpp \
           src/contextvarfabric.cpp

HEADERS += $$files(include/Entities/*.h) \
           $$files(include/Entities/Operators/*.h) \
           $$files(include/Aliases/*.h) \
           $$files(include/Errors/*.h) \
           $$files($$DEFAULT_ENGINE_VERSION_PATH/*.ser) \
           $$files(include/*.h) \
           $$files(include/Logging/*.h)

DEFINES += PRE_ORDER
DEFINES += LITTLE_ENDIAN

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    abi \
    api \
    target
