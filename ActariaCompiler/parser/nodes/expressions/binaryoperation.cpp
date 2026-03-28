#include "binaryoperation.h"


/**
 * @brief BinaryOperation::BinaryOperation
 * @param op
 * @param left
 * @param right
 */
BinaryOperation::BinaryOperation(
    const Token& op,
    Expression* left,
    Expression* right
)
    : op(op), left(left), right(right)
{}

/**
 * @brief BinaryOperation::getOperator
 * @return
 */
const Token &BinaryOperation::getOperator() const
{
    return this->op;
}

/**
 * @brief BinaryOperation::getLeft
 * @return
 */
const Expression &BinaryOperation::getLeft() const
{
    return *this->left;
}

/**
 * @brief BinaryOperation::getRight
 * @return
 */
const Expression &BinaryOperation::getRight() const
{
    return *this->right;
}
