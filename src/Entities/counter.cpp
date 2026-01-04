#include "counter.ser"
#include <QBuffer>
#include <QDataStream>


/**
 * @brief   Counter::Counter
 *          Normal constructor for context counter.
 * @param value
 * @param name
 */
Counter::Counter(value_type value, const QString &name)
    : ContextVar(name), value(value)
{}

/**
 * @brief Counter::hash
 * @return fnv-1A 64 bits hash by class name
 * Uses for identify object type by Actaria VM e.g.
 */
Counter::hash_type Counter::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}

/**
 * @brief Counter::type
 * @return
 */
VarType Counter::type() const
{
    return VarType::Counter;
}

/**
 * @brief Counter::getValue
 * @return trigger-counter
 */
Counter::ContextValue Counter::getValue() const
{
    return this->value;
}

/**
 * @brief Counter::setValue
 * @param value
 */
void Counter::setValue(ContextValue value) noexcept
{
    this->value = std::get<value_type>(value);
}

/**
 * @brief Counter::operator int
 */
Counter::operator int() const noexcept
{
    return this->value;
}
