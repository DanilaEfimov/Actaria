#include "context.ser"

/**
 * @brief Context::Context
 */
Context::Context()
    : Entity(), variables(), characters()
{}

/**
 * @brief Context::Context
 * @param other
 */
Context::Context(Context &&other)
{
    this->merge(std::move(other));
}

/**
 * @brief Context::hash
 * @return fnv-1A 64 bits hash by class name
 * Uses for identify object type by Actaria VM e.g.
 */
Context::hash_type Context::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}

/**
 * @brief Context::merge
 * @param context
 */
void Context::merge(Context&& context)
{
    this->variables.merge(std::move(context.variables));
    this->characters.merge(std::move(context.characters));
}

/**
 * @brief Context::addVariable
 * @param contextvar
 */
void Context::addVariable(contextvar_p contextvar)
{
    this->variables.insert(std::make_pair(contextvar->getName(), std::move(contextvar)));
}

/**
 * @brief Context::addCharacter
 * @param character
 */
void Context::addCharacter(const Character &character)
{
    this->characters.insert(std::make_pair(character.getName(), character));
}

/**
 * @brief Context::removeVariable
 * @param name
 */
void Context::removeVariable(const QString& name)
{
    this->variables.erase(name);
}

/**
 * @brief Context::removeCharacter
 * @param name
 */
void Context::removeCharacter(const key_t& name)
{
    this->characters.erase(name);
}

/**
 * @brief Context::containsVariable
 * @param name
 * @return
 */
bool Context::containsVariable(const key_t& name) const noexcept
{
    return this->variables.contains(name);
}

/**
 * @brief Context::containsCharacter
 * @param name
 * @return
 */
bool Context::containsCharacter(const key_t& name) const noexcept
{
    return this->characters.contains(name);
}

/**
 * @brief Context::empty
 * @return
 */
bool Context::empty() const noexcept
{
    return this->size() == 0;
}

void Context::clear() noexcept
{
    this->variables.clear();
    this->characters.clear();
}

/**
 * @brief Context::size
 * @return
 */
qsizetype Context::size() const noexcept
{
    return this->characters.size() + this->variables.size();
}

/**
 * @brief Context::equals
 * @param name
 * @param value
 * @return
 */
bool Context::equals(const QString &name, value_types value) const
{
    auto it = variables.find(name);
    if (it == variables.end())
        return false;

    return it->second->getValue() == value;
}

/**
 * @brief Context::set
 * @param name
 * @param value
 */
void Context::set(const QString &name, value_types value)
{
    if(!this->containsVariable(name))
        return;

    this->variables[name]->setValue(value);
}

/**
 * @brief Context::getValue
 * @param name
 * @return
 */
const Context::value_types Context::getValue(const QString &name) const noexcept
{
    auto it = variables.find(name);
    if (it == variables.end())
        return false;

    return it->second->getValue();
}
