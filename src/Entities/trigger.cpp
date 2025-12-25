#include "Entities/trigger.h"
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>
#include <QVariant>

namespace {
    constexpr const char* typeName = "Trigger";
    constexpr const int fieldCount = 2;
};

/**
 * @brief Trigger::Trigger
 *
 * Normal constructor for context counter.
 *
 * @param value
 *
 * @param name
 */
Trigger::Trigger(value_type value, const QString &name)
    : ContextVar(name), value(value) {}

/**
 * @brief Trigger::Trigger
 *
 * Non global entity counter increment.
 * Hex parse-based constructor.
 *
 * @param represent
 */
Trigger::Trigger(const QStringList &represent)
    : ContextVar()
{
}

/**
 * @brief Trigger::Trigger
 *
 * Non global entity counter increment.
 * QString parse-based constructor.
 *
 * @param represent
 */
Trigger::Trigger(const QByteArray &represent)
    : ContextVar()
{
}

/**
 * @brief Trigger::getValue
 *
 * @return trigger-value
 */
Trigger::value_type Trigger::getValue() const
{
    return this->value;
}

/**
 * @brief Trigger::setValue
 *
 * @param value
 */
void Trigger::setValue(value_type value) noexcept
{
    this->value = value;
}

/**
 * @brief Trigger::operator bool
 */
Trigger::operator bool() const noexcept
{
    return this->value;
}

QByteArray Trigger::hexHeader() const
{

}

QStringList Trigger::strHeader() const
{

}
