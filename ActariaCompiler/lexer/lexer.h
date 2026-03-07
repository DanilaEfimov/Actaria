#ifndef LEXER_H
#define LEXER_H

#include "token.h"

#include <QString>
#include <QVector>


class Token;

struct Position {
    int line;
    int column;
};

typedef QVector<QString> text_t;

class Lexer
{
    QVector<text_t> source;
    Position pos;

    void increment() noexcept;

    static TokenCategory checkCategory(const QString& value);

public:
    Lexer(const text_t& source);

    Token nextToken();

    Token peekToken(int n = 0) const;

    bool isEof() const;

    Position getPosition() const;
};

#endif // LEXER_H
