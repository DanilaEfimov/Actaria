#include "Entities/Operators/assignmentoperator.h"


/**
 * @brief AssignmentOperator::AssignmentOperator
 * @param lvalue
 * @param rvalue
 */
AssignmentOperator::AssignmentOperator(ContextVar *lvalue, AlgebraExpression &&rvalue)
    : Operator(), lvalue(lvalue), rvalue(std::move(rvalue))
{}
