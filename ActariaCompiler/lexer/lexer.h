#ifndef LEXER_H
#define LEXER_H

#include "token.h"

#include <QStringList>

struct Position {
    int line = 0;
    int column = 0;
};

class Lexer
{
    QStringList source;
    QStringList currentWords;
    Position pos;

    void increment() noexcept;
    void tokenizeCurrentLine();
    static TokenCategory checkCategory(const QString& value);

    Token collectTextLiteral();

public:
    explicit Lexer(const QStringList& sourceLines);

    Token nextToken();

    Token peekToken(int n = 0) const;

    bool isEof() const;

    Position getPosition() const;
};

#endif // LEXER_H
