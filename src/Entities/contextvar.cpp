#include "Entities/contextvar.h"


/**
 * @brief ContextVar::ContextVar
 */
ContextVar::ContextVar()
    : Entity(NonIncrementFlag{}), name()
{}

/**
 * @brief ContextVar::ContextVar
 * @param name
 */
ContextVar::ContextVar(const QString &name)
    : Entity(), name(name)
{}

/**
 * @brief ContextVar::getName
 * @return name of variable
 */
QString ContextVar::getName() const
{
    return this->name;
}

/**
 * @brief ContextVar::setName
 * @param name
 */
void ContextVar::setName(const QString &name) noexcept
{
    this->name = name;
}
