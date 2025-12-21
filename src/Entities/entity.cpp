#include "Entities/entity.h"
#include "utils.h"
#include <QStringList>
#include <QBuffer>

namespace {
    constexpr const char* typeName = "Entity";
    constexpr const int fieldCount = 2;
};

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
 * Just calls Entity::fromString(const QStringList&).
 */
Entity::Entity(const QStringList &represent)
{
    this->fromString(represent);
}

/**
 * @brief Entity::Entity
 * @param represent (const QByteArray&)
 * Just calls Entity::deserialize(const QByteArray&)
 */
Entity::Entity(const QByteArray &represent)
{
    this->deserialize(represent);
}

/**
 * @brief Entity::minimumSize
 * @return minimum required size of QByteArray to deserialize
 */
quint32 Entity::minimumSize() const
{
    return sizeof(Entity::id_type);
}

/**
 * @brief Entity::minimumStrings
 * @return count of required strings in representation
 */
quint32 Entity::minimumStrings() const
{
    return fieldCount;
}

/**
 * @brief Entity::hash
 * @return fnv-1A 64 bits hash by class name
 * Uses for identify object type by Actaria VM e.g.
 */
Entity::hash_type Entity::hash() const
{
    return utils::fnv1a_64(typeName);
}

/**
 * @brief Entity::size
 * @return actuall size of serialized object in bytes
 */
size_t Entity::size() const
{
    return sizeof(hash_type) + sizeof(id_type);
}

/**
 * @brief Entity::serialize
 * @return binary serialized onject
 */
QByteArray Entity::serialize() const
{
    QByteArray ret;
    QDataStream out(&ret, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    out << static_cast<id_type>(this->id);

    return ret;
}

/**
 * @brief Entity::deserialize
 * @param data (const QByteArray&)
 * Parsing prefix-formated binary data and rewrite object
*/
void Entity::deserialize(const QByteArray& data)
{
    if(data.size() < this->Entity::minimumSize()){
        qWarning("Entity::deserialize: data too small");
        return;
    }

    QBuffer buffer;
    buffer.setData(data);
    buffer.open(QIODevice::ReadOnly);

    QDataStream in(&buffer);
    in.setVersion(QDataStream::Qt_6_5);

    in >> this->id;
}

/**
 * @brief Entity::represent
 * @return readable representation of object
 */
QString Entity::represent() const
{
    return QStringList{
        typeName,
        QString::number(this->id)
    }.join(separator);
}

/**
 * @brief Entity::fromString
 * @param data (const QStringList&)
 * Parsing QStringList and rewrites object
 */
void Entity::fromString(const QStringList &data)
{
    if(data.size() < this->minimumSize()){
        qWarning("Entity::fromString: data too small");
        return;
    }

    bool ok;
    this->id = static_cast<id_type>(data[1 + IdField].toInt(&ok));
    if(!ok){
        qWarning("Entity::Failed to parse entity id");
    }
}

/**
 * @brief Entity::getId
 * @return unique id of game entity
 */
Entity::id_type Entity::getId() const
{
    return this->id;
}
