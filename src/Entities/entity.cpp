#include "Entities/entity.h"
#include "utils.h"
#include "engineinfo.h"
#include <QStringList>
#include <QBuffer>


/**
 * @brief The entity_traits class
 * byte and words measuring traits for Entity
 */
template<abi::Version V>
struct entity_traits<Entity, V> {
    static constexpr bool is_fixed = true;
    static constexpr int minimum_bytes = sizeof(Entity::id_type);
    static constexpr int maximum_bytes = minimum_bytes;

    static constexpr const char* name = "Entity";
    static constexpr int minimum_words = 1;
    static constexpr int maximum_words = minimum_words;
};

/**
 * @brief The Writer class
 * version generalized write interface
 */
template<abi::Version V>
struct Writer<Entity, V> {
    static void write(QDataStream& out, const Entity& e) {
        out << e.hexHeader().constData();
    }

    static void write(QStringList& out, const Entity& e) {
        out << e.strHeader();
    }
};

/**
 * @brief The Reader class
 * version generalized read interface
 */
template<abi::Version V>
struct Reader<Entity, V> {
    static void read(QDataStream& in, Entity& e) {
        in >> e.id;
    }

    static void read(const QStringList& in, Entity& e) {
        bool ok = true;
        e.id = static_cast<Entity::id_type>(in.at(0).toLongLong(&ok));

        if(!ok){
            qWarning("Reader<Entity, V>::read: can not to parse id from: %s",
                     in.empty() ? "<empty>" : in.at(0).toStdString().c_str());
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
 * @brief Entity::hash
 * @return fnv-1A 64 bits hash by class name
 * Uses for identify object type by Actaria VM e.g.
 */
constexpr Entity::hash_type Entity::hash() const
{
    using entity_t = std::remove_cvref_t<decltype(*this)>;
    constexpr auto version = EngineInfo::defaultVersion;

    return utils::fnv1a_64(entity_traits<entity_t, version>::name);
}

/**
 * @brief Entity::hexHeader
 * @return dumped fields of *this
 */
QByteArray Entity::hexHeader() const
{
    QByteArray ret;
    ret.append(this->id);

    return ret;
}

/**
 * @brief Entity::strHeader
 * @return human readable header
 */
QStringList Entity::strHeader() const
{
    return QStringList{QString::number(this->id)};
}

/**
 * @brief Entity::getId
 * @return unique id of game entity
 */
Entity::id_type Entity::getId() const
{
    return this->id;
}
