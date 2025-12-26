#include "Entities/counter.h"
#include <QBuffer>
#include <QDataStream>


/**
 * @brief Counter::Counter
 * Normal constructor for context counter.
 * @param value
 * @param name
 */
Counter::Counter(value_type value, const QString &name)
    : ContextVar(name), value(value)
{}

/**
 * @brief Counter::getValue
 * @return trigger-counter
 */
Counter::value_type Counter::getValue() const
{
    return this->value;
}

/**
 * @brief Counter::setValue
 * @param value
 */
void Counter::setValue(value_type value) noexcept
{
    this->value = value;
}

/**
 * @brief Counter::operator int
 */
Counter::operator int() const noexcept
{
    return this->value;
}
