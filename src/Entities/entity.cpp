#include "entity.ser"
#include "Entities/entity.h"
#include "common.h"
#include "engineinfo.h"


uint32_t Entity::counter = 0;

/**
 * @brief Entity::Entity
 * Default indexing constructor.
 */
Entity::Entity()
    : id(++Entity::counter)
{}

/**
 * @brief Entity::Entity
 * Fake protected constructor for parse-based constructors.
 * Don't increments Entity counter, because id must be parsed.
 */
Entity::Entity(NonIncrementFlag &&)
    : id(UNDEFINED_ID)
{}

/**
 * @brief Entity::Entity
 * @param represent (const QStrinList&)
 */
Entity::Entity(QStringList &represent)
{
    StringListCursor cursor(represent);
    Reader<Entity, EngineInfo::defaultVersion>::read(cursor, *this);
}

/**
 * @brief Entity::Entity
 * @param represent (const QByteArray&)
 */
Entity::Entity(const QByteArray &represent)
{
    QDataStream in(represent);
    Reader<Entity, EngineInfo::defaultVersion>::read(in, *this);
}

/**
 * @brief Entity::getId
 * @return unique id of game entity
 */
Entity::id_type Entity::getId() const
{
    return this->id;
}

/**
 * @brief Entity::operator ==
 * @param other
 * @return true if id equals
 */
bool Entity::operator==(const Entity &other) const
{
    return this->id == other.id;
}
