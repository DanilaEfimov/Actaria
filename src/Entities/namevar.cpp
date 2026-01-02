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
 * @brief NameVar::type
 * @return
 */
VarType NameVar::type() const
{
    return VarType::Name;
}

/**
 * @brief NameVar::getValue
 * @return contained value of variable
 */
NameVar::ContextValue NameVar::getValue() const
{
    return this->value;
}

/**
 * @brief NameVar::setValue
 * @param value
 */
void NameVar::setValue(ContextValue value) noexcept
{
    this->value = std::get<QString>(value);
}
