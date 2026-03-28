#ifndef NUMBERLITERAL_H
#define NUMBERLITERAL_H

#include "parser/nodes/expression.h"

class NumberLiteral : public Expression
{
    int value;

public:
    explicit NumberLiteral(int value);

    int getValue() const;
};

#endif // NUMBERLITERAL_H
