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
    : Entity(), context(context) {}

/**
 * @brief Context::merge
 * @param other
 */
void Context::merge(Context&& other)
{
    this->context.insert(other.context);
}

void Context::remove(const QString &name)
{

}

void Context::clear()
{

}
