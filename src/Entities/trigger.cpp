#include "trigger.ser"
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
 * @brief Trigger::hash
 * @return fnv-1A 64 bits hash by class name
 * Uses for identify object type by Actaria VM e.g.
 */
Trigger::hash_type Trigger::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}

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
