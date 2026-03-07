#include "parser/nodes/expressions/unaryoperation.h"


/**
 * @brief UnaryOperation::UnaryOperation
 * @param op
 * @param operand
 */
UnaryOperation::UnaryOperation(const Token& op, Expression* operand)
    : op(op), operand(operand)
{}

/**
 * @brief UnaryOperation::getOperator
 * @return
 */
const Token &UnaryOperation::getOperator() const
{
    return this->op;
}

/**
 * @brief UnaryOperation::getOperand
 * @return
 */
const Expression& UnaryOperation::getOperand() const
{
    return *this->operand;
}


