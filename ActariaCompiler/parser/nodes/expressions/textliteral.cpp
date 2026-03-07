#include "parser/nodes/expressions/textliteral.h"


/**
 * @brief TextLiteral::TextLiteral
 * @param value
 */
TextLiteral::TextLiteral(QString value)
    : value(value)
{}

/**
 * @brief TextLiteral::getValue
 * @return
 */
QString TextLiteral::getValue() const
{
    return this->value;
}
