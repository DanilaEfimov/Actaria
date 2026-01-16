#include "namevar.ser"
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
 * @brief NameVar::hash
 * @return fnv-1A 64 bits hash by class name
 * Uses for identify object type by Actaria VM e.g.
 */
NameVar::hash_type NameVar::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}

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

/**
 * @brief NameVar::operator QString
 */
NameVar::operator QString() const noexcept
{
    return this->value;
}
