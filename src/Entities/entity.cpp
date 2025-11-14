#include "Entities/entity.h"
#include "utils.h"
#include <QStringList>
#include <QBuffer>

namespace {
    constexpr const char* typeName = "Entity";
};

uint32_t Entity::counter = 0;

/**
 * @brief Entity::Entity
 *
 * Default indexing constructor.
 */
Entity::Entity()
    : id(++Entity::counter) {}

/**
 * @brief Entity::Entity
 *
 * Fake protected constructor for parse-based constructors.
 * Don't increments Entity counter, because id must be parsed.
 */
Entity::Entity(NonIncrementFlag &&) {}

/**
 * @brief Entity::Entity
 *
 * Just calls Entity::fromString(const QStringList&).
 *
 * @param represent (const QStrinList&)
 */
Entity::Entity(const QStringList &represent)
{
    this->fromString(represent);
}

/**
 * @brief Entity::Entity
 *
 * Just calls Entity::deserialize(const QByteArray&).
 *
 * @param represent (const QByteArray&)
 */
Entity::Entity(const QByteArray &represent)
{
    this->deserialize(represent);
}

/**
 * @brief Entity::minimumSize
 *
 * @return minimum required size of QByteArray to deserialize
 */
quint32 Entity::minimumSize() const
{
    return sizeof(Entity::id_type);
}

/**
 * @brief Entity::hash
 *
 * @return fnv-1A 64 bits hash by class name
 *
 * Uses for identify object type by Actaria VM e.g.
 */
Entity::hash_type Entity::hash() const
{
    return utils::fnv1a_64(typeName);
}

/**
 * @brief Entity::size
 *
 * @return actuall size of serialized object in bytes
 */
size_t Entity::size() const
{
    return sizeof(hash_type) + sizeof(id_type);
}

/**
 * @brief Entity::serialize
 *
 * @return binary serialized onject
 */
QByteArray Entity::serialize(bool isPostfix) const
{
    QByteArray ret;
    QDataStream out(&ret, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    if(!isPostfix)
        out << static_cast<hash_type>(this->hash());
    out << static_cast<id_type>(this->id);

    return ret;
}

/**
 * @brief Entity::deserialize
 *
 * Parsing prefix-formated binary data and rewrite object.
 *
 * @param data (const QByteArray&)
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
 *
 * @return readable representation of object
 */
QString Entity::represent() const
{
    return QStringList{typeName, QString::number(this->id)}.join(separator);
}

/**
 * @brief Entity::fromString
 *
 * Parsing QStringList and rewrites object.
 *
 * @param data (const QStringList&)
 */
void Entity::fromString(const QStringList &data)
{
    if(data.size() < 2){
        qWarning("Entity::fromString: data too small");
        return;
    }

    bool ok;
    this->id = static_cast<id_type>(data[1].toInt(&ok));
    if(!ok){
        qWarning("Entity::Failed to parse entity id");
    }
}

/**
 * @brief Entity::getId
 *
 * @return unique id of game entity
 */
Entity::id_type Entity::getId() const
{
    return this->id;
}
