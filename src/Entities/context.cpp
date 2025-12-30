#include "Entities/context.h"


/**
 * @brief Context::Context
 */
Context::Context()
    : Entity() {}

/**
 * @brief Context::Context
 * @param context
 */
Context::Context(const QMap<QString, value_type> &context)
    : Entity(), context()
{
    for(auto& variable : context){

    }
}

/**
 * @brief Context::size
 * @return actual count of context variables
 */
qsizetype Context::size() const
{
    return this->context.size();
}

/**
 * @brief Context::merge
 * @param other
 */
void Context::merge(Context&& other)
{
    //this->context.insert(std::move(other.context));
}

/**
 * @brief Context::remove
 * @param name
 */
void Context::remove(const QString &name)
{
    //this->context.remove(name);
}

/**
 * @brief Context::clear
 */
void Context::clear()
{
    this->context.clear();
}
