#include "parser/nodes/expressions/numberliteral.h"


/**
 * @brief NumberLiteral::NumberLiteral
 * @param value
 */
NumberLiteral::NumberLiteral(int value)
    : value(value)
{}

/**
 * @brief NumberLiteral::getValue
 * @return
 */
int NumberLiteral::getValue() const
{
    return this->value;
}
