#include "parser/nodes/expressions/triggerliteral.h"


/**
 * @brief TriggerLiteral::TriggerLiteral
 * @param value
 */
TriggerLiteral::TriggerLiteral(bool value)
    : value(value)
{}

/**
 * @brief TriggerLiteral::getValue
 * @return
 */
bool TriggerLiteral::getValue() const
{
    return this->value;
}
