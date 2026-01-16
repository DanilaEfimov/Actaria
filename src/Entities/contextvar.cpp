#include "contextvar.ser"
#include "utils.h"


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
 * @brief ContextVar::hash
 * @return fnv-1A 64 bits hash by class name
 * Uses for identify object type by Actaria VM e.g.
 */
ContextVar::hash_type ContextVar::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}

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

/**
 * @brief ContextVar::setValueSafe
 * @param value : ContextValue
 * @return  true if given value type matches and it's updated.
 *          false otherwise.
 */
bool ContextVar::setValueSafe(ContextValue value)
{
    if(typeOf(value) != this->type())
        return false;

    this->setValue(value);

    return true;
}
