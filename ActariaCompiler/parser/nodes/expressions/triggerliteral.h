#ifndef TRIGGERLITERAL_H
#define TRIGGERLITERAL_H

#include "parser/nodes/expression.h"


class TriggerLiteral : public Expression
{
    bool value;

public:
    explicit TriggerLiteral(bool value);

    bool getValue() const;
};

#endif // TRIGGERLITERAL_H
