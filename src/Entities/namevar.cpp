#include "Entities/namevar.h"
#include <QDataStream>


/**
 * @brief NameVar::NameVar
 * @param value
 * @param name
 */
NameVar::NameVar(value_type value, const QString &name)
    : ContextVar(name), value(value)
{}

/**
 * @brief NameVar::getValue
 * @return contained value of variable
 */
NameVar::value_type NameVar::getValue() const
{
    return this->value;
}

/**
 * @brief NameVar::setValue
 * @param value
 */
void NameVar::setValue(value_type value) noexcept
{
    this->value = value;
}
