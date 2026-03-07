#ifndef TEXTLITERAL_H
#define TEXTLITERAL_H

#include "parser/nodes/expression.h"

#include <QString>

class TextLiteral : public Expression
{
    QString value;

public:
    explicit TextLiteral(QString value);

    QString getValue() const;
};

#endif // TEXTLITERAL_H
