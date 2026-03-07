QT = core

CONFIG += c++17 cmdline

SOURCES += \
        $$files(lexer/*.cpp) \
        argparser.cpp \
        config.cpp \
        lexer/literals.cpp \
        lexer/pointing.cpp \
        lexer/token.cpp \
        main.cpp \
        parser/node.cpp \
        parser/nodes/expression.cpp \
        parser/nodes/expressions/identifier.cpp \
        parser/nodes/expressions/numberliteral.cpp \
        parser/nodes/expressions/textliteral.cpp \
        parser/nodes/expressions/triggerliteral.cpp \
        parser/nodes/expressions/unaryoperation.cpp \
        parser/nodes/statemate.cpp \
        parser/parser.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    $$files(lexer/*.h) \
    argparser.h \
    config.h \
    lexer/literals.h \
    parser/node.h \
    parser/nodes/expression.h \
    parser/nodes/expressions/identifier.h \
    parser/nodes/expressions/numberliteral.h \
    parser/nodes/expressions/textliteral.h \
    parser/nodes/expressions/triggerliteral.h \
    parser/nodes/expressions/unaryoperation.h \
    parser/nodes/statemate.h \
    parser/parser.h
