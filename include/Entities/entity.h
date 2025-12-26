/**
 * @file entity.h
 * Base class for a game entity.
 * Provides an interface for identification and serialization.
 * Derived classes: Scene, Dialog, Trigger, and other game objects.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "utils.h"
#include "readwrite.h"
#include "stringlistcursor.h"
#include <QString>
#include <QByteArray>

#define UNDEFINED_ID (static_cast<Entity::id_type>(-1))

using namespace abi;

class Entity
{
    ACT_SERIALIZABLE

    static uint32_t counter;

public:
    using base_t = void;  // absolute base type pattern
    using hash_type = utils::hash_type;
    using id_type = utils::id_type;

protected:
    id_type id;

    struct NonIncrementFlag {};

    Entity();
    Entity(NonIncrementFlag&&);
    Entity(QStringList& represent);
    Entity(const QByteArray& represent);

public:
    virtual ~Entity() = default;

    constexpr hash_type hash() const;

    id_type getId() const;
};


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
    static constexpr int minimum_words = 2;
    static constexpr int maximum_words = minimum_words;
};

/**
 * @brief The Writer class
 * version generalized write interface
 */
template<abi::Version V>
struct Writer<Entity, V> {
    static void write(QDataStream& out, const Entity& e) {
        out << e.id;
    }

    static void write(StringListCursor& out, const Entity& e) {
        out.append(entity_traits<Entity, V>::name);
        out.append(QString::number(e.id));
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

    static void read(StringListCursor& in, Entity& e) {
        bool ok = true;

        if(in.remaining() < entity_traits<Entity, V>::minimum_words){
            ok = false;
            e.id = UNDEFINED_ID;
        }
        else {
            e.id = static_cast<Entity::id_type>(in.next().toLongLong(&ok));
        }

        if(!ok){
            qWarning() << "Reader<Entity, V>::read: can not parse id from: " << in.peek();
        }

        in.skip();  // skipping this->id field
    }
};

#endif // ENTITY_H
