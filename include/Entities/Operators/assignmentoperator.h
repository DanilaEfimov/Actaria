#ifndef ASSIGNMENTOPERATOR_H
#define ASSIGNMENTOPERATOR_H

#include "operator.h"
#include "contextalgebra.h"


class AssignmentOperator : public Operator
{
    ACT_SERIALIZABLE

    ContextVar* lvalue;
    AlgebraExpression rvalue;

public:
    using base_t = Operator;

    AssignmentOperator(ContextVar* lvalue, AlgebraExpression&& rvalue);;
};

#endif // ASSIGNMENTOPERATOR_H
