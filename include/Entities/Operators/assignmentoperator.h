#ifndef ASSIGNMENTOPERATOR_H
#define ASSIGNMENTOPERATOR_H

#include "operator.h"
#include "Entities/contextvar.h"


class AssignmentOperator : public Operator
{
    ACT_SERIALIZABLE

public:
    using ContextValue = ContextVar::ContextValue;

    id_type lvalue;
    ContextValue rvalue;

public:
    using base_t = Operator;

    AssignmentOperator(id_type lvalue, ContextValue rvalue);

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;
};

#endif // ASSIGNMENTOPERATOR_H
