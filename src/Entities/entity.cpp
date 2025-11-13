#include "Entities/entity.h"
#include "utils.h"
#include <QStringList>
#include <QBuffer>

namespace {
    constexpr const char* typeName = "Entity";
};

uint32_t Entity::counter = 0;

Entity::Entity()
    : id(++Entity::counter) {}

Entity::Entity(const QStringList &represent)
{
    this->fromString(represent);
}

Entity::Entity(const QByteArray &represent)
{
    this->deserialize(represent);
}

Entity::hash_type Entity::hash() const
{
    return utils::fnv1a_64(typeName);
}

size_t Entity::size() const
{
    return sizeof(hash_type) + sizeof(id_type);
}

QByteArray Entity::serialize() const
{
    QByteArray ret;
    QDataStream out(&ret, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    out << static_cast<hash_type>(this->hash())
        << static_cast<id_type>(this->id);

    return ret;
}

void Entity::deserialize(const QByteArray& data)
{
    /**
     * [hash code][id]
     * hash code ignored for constructing
     * hash code needable only for identify entity type
    */
    QBuffer buffer(const_cast<QByteArray*>(&data));
    buffer.open(QIODevice::ReadOnly);

    QDataStream in(&buffer);
    in.setVersion(QDataStream::Qt_6_5);

    in.device()->seek(sizeof(utils::hash_type));
    in >> this->id;
}

QString Entity::represent() const
{
    return QStringList{typeName, QString::number(this->id)}.join(separator);
}

void Entity::fromString(const QStringList &data)
{
    /**
     * [hash code][id]
     * hash code ignored for constructing
     * hash code needable only for identify entity type
    */
    if(data.size() < 2){
        throw std::invalid_argument("Entity::Not enough elements for parsing.");
    }

    bool parseError;
    this->id = static_cast<id_type>(data[1].toInt(&parseError));
    if(parseError){
        throw std::invalid_argument("Entity::Failed to parse entity id.");
    }
}

Entity::id_type Entity::getId() const
{
    return this->id;
}
