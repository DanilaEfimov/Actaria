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
Context::Context(const QMap<QString, value_type> context)
    : Entity(), context(context) {}

/**
 * @brief Context::minimumSize
 * @return
 */
quint32 Context::minimumSize() const
{
}

/**
 * @brief Context::minimumStrings
 * @return
 */
quint32 Context::minimumStrings() const
{
}

/**
 * @brief Context::hash
 * @return
 */
Entity::hash_type Context::hash() const
{
}

/**
 * @brief Context::size
 * @return
 */
size_t Context::size() const
{
}

/**
 * @brief Context::serialize
 * @return
 */
QByteArray Context::serialize() const
{
}

/**
 * @brief Context::deserialize
 * @param data
 */
void Context::deserialize(const QByteArray& data)
{
}

/**
 * @brief Context::represent
 * @return
 */
QString Context::represent() const
{
}

/**
 * @brief Context::fromString
 * @param data
 */
void Context::fromString(const QStringList& data)
{
}

/**
 * @brief Context::remove
 * @param name
 */
void Context::remove(const QString& name)
{

}
