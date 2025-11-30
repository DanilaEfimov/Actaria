#ifndef ASSIGNMENTOPERATOR_H
#define ASSIGNMENTOPERATOR_H

#include "Entities/operator.h"
#include "Entities/contextvar.h"

enum class arithmetic_op : int;

class AssignmentOperator : public Operator
{
    std::shared_ptr<ContextVar> lvalue;

public:
    AssignmentOperator(ContextVar* lvalue);
};

#endif // ASSIGNMENTOPERATOR_H
