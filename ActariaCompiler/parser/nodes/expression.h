#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "parser/nodes/statemate.h"

class Expression : public Statement
{
public:
    virtual ~Expression() = default;
};

#endif  // EXPRESSION_H
