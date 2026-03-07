#include "parser/nodes/expressions/identifier.h"


/**
 * @brief Identifier::Identifier
 * @param name
 */
Identifier::Identifier(const QString& name)
    : name(name)
{}

/**
 * @brief Identifier::getName
 * @return
 */
const QString &Identifier::getName() const
{
    return this->name;
}
