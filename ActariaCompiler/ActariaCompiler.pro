QT = core
CONFIG += c++17 cmdline

CONFIG += staticlib

contains(CONFIG, staticlib) {
    TEMPLATE = lib
    CONFIG -= console
    TARGET = actaria_lib
    DESTDIR = $$PWD/build
} else {
    TEMPLATE = app
    TARGET = actaria_compiler
}

SOURCES += \
    $$files(lexer/*.cpp) \
    $$files(parser/*.cpp) \
    $$files(parser/nodes/*.cpp) \
    $$files(parser/nodes/expressions/*.cpp) \
    $$files(parser/nodes/statement/*.cpp) \
    $$files(./*.cpp) \
    $$files(preprocessor/*.cpp)

HEADERS += \
    $$files(lexer/*.h) \
    $$files(parser/*.h) \
    $$files(parser/nodes/*.h) \
    $$files(parser/nodes/expressions/*.h) \
    $$files(parser/nodes/statement/*.h) \
    $$files(./*.h) \
    $$files(preprocessor/*.h)
