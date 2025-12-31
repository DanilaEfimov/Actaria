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

#include "entity.ser"

#endif // ENTITY_H
