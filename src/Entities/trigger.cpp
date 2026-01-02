#include "Entities/trigger.h"
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>
#include <QVariant>


/**
 * @brief Trigger::Trigger
 * @param value
 * @param name
 */
Trigger::Trigger(value_type value, const QString &name)
    : ContextVar(name), value(value) {}

/**
 * @brief Trigger::type
 * @return
 */
VarType Trigger::type() const
{
    return VarType::Trigger;
}

/**
 * @brief Trigger::getValue
 * @return trigger-value
 */
Trigger::ContextValue Trigger::getValue() const
{
    return this->value;
}

/**
 * @brief Trigger::setValue
 * @param value
 */
void Trigger::setValue(ContextValue value) noexcept
{
    this->value = std::get<bool>(value);
}

/**
 * @brief Trigger::operator bool
 */
Trigger::operator bool() const noexcept
{
    return this->value;
}
