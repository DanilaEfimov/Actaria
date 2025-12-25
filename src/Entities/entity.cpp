#include "Entities/entity.h"
#include "utils.h"
#include "engineinfo.h"
#include <QStringList>
#include <QBuffer>

namespace {
    constexpr const char* typeName = "Entity";
    constexpr const int fieldCount = 1;
};

template<>
struct abi::Writer<Entity, abi::Version::Act_1_0> {
    static void write(QDataStream& out, const Entity& obj) {
        out << obj.id;
    }

    static void write(QStringList& out, const Entity& obj) {
        out.append(QStringList{
            typeName,
            QString::number(obj.id)
        });
    }
};

template <>
struct abi::Reader<Entity, abi::Version::Act_1_0> {
    static void read(QDataStream& in, Entity& obj){
        in >> obj.id;
    }

    static void read(const QStringList& in, Entity& obj) {
        if(in.size() < 2){
            qWarning("abi::Reader<Entity, abi::Version::Act_1_0>: not enought words for parsing: %s",
                     in.join(Entity::separator).toStdString().c_str());
            return;
        }

        bool ok = true;
        obj.id = static_cast<Entity::id_type>(in.at(1).toLongLong(&ok));

        if(!ok){
            qWarning("abi::Reader<Entity, abi::Version::Act_1_0>: failed to parse id from expr: %s",
                     in.at(1).toStdString().c_str());
        }
    }
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
 */
Entity::Entity(const QStringList &represent)
{
    Reader<Entity, EngineInfo::defaultVersion>::read(represent, *this);
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
