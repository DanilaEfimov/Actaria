#include "Entities/assignmentoperator.h"

enum class arithmetic_op : int {
    constant,   // ... = C
    plus,
    minus,
    mul,
    div,
    rem,
    power,
    min,        // ... = min(...) - minimum of ...
    max,        // ... = max(...) - maximum of ...
    random      // ... = random(...) - random of ...
};

AssignmentOperator::AssignmentOperator(ContextVar *lvalue)
    : Operator(), lvalue(lvalue)
{}
