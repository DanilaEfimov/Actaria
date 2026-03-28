#ifndef KEYWORD_H
#define KEYWORD_H

#include "lexer/token.h"

#include <QString>

class Keyword
{
    QString word;

public:
    Keyword(const Keyword&) = default;
    explicit Keyword(const Token& token);

    const QString& get() const;
};

#endif // KEYWORD_H
