#ifndef LEXER_H
#define LEXER_H

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
    const text_t source;
    Position pos;

public:
    Lexer(const text_t& source);

    Token nextToken() const;

    Token peekToken(int n = 0) const;

    bool isEof() const;

    Position getPosition() const;
};

#endif // LEXER_H
