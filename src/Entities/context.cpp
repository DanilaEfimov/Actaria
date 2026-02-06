#include "context.ser"
#include "Errors/nosuchid.h"
#include "Logging/logcore.h"


/**
 * @brief Context::Context
 */
Context::Context()
    : Entity(),
    variables(),
    characters(),
    callStack()
{}

/**
 * @brief Context::Context
 * @param other
 */
Context::Context(Context&& other)
    : Entity(),
    variables(),
    characters(),
    callStack()
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
 * @brief Context::stackDepth
 * @return
 */
int Context::stackDepth() const noexcept
{
    return static_cast<int>(this->callStack.size());
}

/**
 * @brief Context::top
 * @return  last called event pointer if call stack is not empty,
 *          nullptr otherwise.
 */
Context::event_ptr Context::top() const noexcept
{
    if(this->callStack.empty())
        return nullptr;

    return this->callStack.top();
}

/**
 * @brief Context::stackEmpty
 * @return  true if call stack is empty,
 *          false otherwise.
 */
bool Context::stackEmpty() const noexcept
{
    return this->callStack.empty();
}

/**
 * @brief Context::pushEvent
 * @param event
 */
void Context::pushEvent(event_ptr event)
{
    this->callStack.push(event);
}

/**
 * @brief Context::popEvent
 */
void Context::popEvent()
{
    if(!this->stackEmpty())
        this->callStack.pop();

    else if(logCore().isDebugEnabled())
        qWarning(logCore) << "Context::popEvent: event stack is empty";
}

/**
 * @brief Context::addVariable
 * @param contextvar
 */
void Context::addVariable(contextvar_p contextvar)
{
    this->variables.insert(std::make_pair(contextvar->getId(), std::move(contextvar)));
}

/**
 * @brief Context::addCharacter
 * @param character
 */
void Context::addCharacter(const Character &character)
{
    this->characters.insert(std::make_pair(character.getId(), character));
}

/**
 * @brief Context::removeVariable
 * @param key
 */
void Context::removeVariable(const Entity::id_type& key)
{
    this->variables.erase(key);
}

/**
 * @brief Context::removeCharacter
 * @param name
 */
void Context::removeCharacter(const key_t& key)
{
    this->characters.erase(key);
}

/**
 * @brief Context::containsVariable
 * @param name
 * @return
 */
bool Context::containsVariable(const key_t& key) const noexcept
{
    return this->variables.contains(key);
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

/**
 * @brief Context::clear
 */
void Context::clear() noexcept
{
    this->variables.clear();
    this->characters.clear();
    while(!this->callStack.empty()) this->callStack.pop();
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
bool Context::equals(const key_t& key, value_types value) const
{
    auto it = variables.find(key);
    if (it == variables.end())
        throw NoSuchId(key, abi::entity_traits<ContextVar, EngineInfo::defaultVersion>::name);

    return it->second->getValue() == value;
}

/**
 * @brief Context::set
 * @param name
 * @param value
 * @throws NoSuchId exception if there isn't such variable.
 */
void Context::set(const key_t& key, value_types value)
{
    if(!this->containsVariable(key))
        throw NoSuchId(key, abi::entity_traits<ContextVar, EngineInfo::defaultVersion>::name);

    this->variables[key]->setValue(value);
}

/**
 * @brief Context::getValue
 * @param name
 * @return  Value of context variable with such id
 */
const Context::value_types Context::getValue(const key_t& key) const
{
    auto it = variables.find(key);
    if (it == variables.end())
        throw NoSuchId(key, abi::entity_traits<ContextVar, EngineInfo::defaultVersion>::name);

    return it->second->getValue();
}
