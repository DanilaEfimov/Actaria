#include "import.h"


/**
 * @brief Import::Import
 * @param symbol
 */
Import::Import(const Identifier& symbol)
    : symbol(symbol)
{}


/**
 * @brief Import::getName
 * @return
 */
const QString &Import::getName() const
{
    return this->symbol.getName();
}
