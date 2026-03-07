#ifndef STATEMENT_H
#define STATEMENT_H

#include "parser/node.h"

class Statement : public Node
{
public:
    virtual ~Statement() = default;
};

#endif  // STATEMATE_H
