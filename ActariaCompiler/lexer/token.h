#ifndef TOKEN_H
#define TOKEN_H

#include <QString>

enum class TokenCategory : uint8_t {
    Identifier,
    Keyword,
    StringLiteral,
    NumberLiteral,
    SingleComment,
    LBrace,
    RBrace,
    Eof
};

class Token {
    TokenCategory category;
    QString value;

public:
    Token(TokenCategory cat, const QString& val = QString())
        : category(cat), value(val) {}

    TokenCategory getCategory() const { return category; }
    const QString& getValue() const { return value; }
};

#endif // TOKEN_H
