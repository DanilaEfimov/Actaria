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

namespace abi {

    enum EntityFieldsOrder {
        IdField,    // id_type
    };

};  // namespace abi

using namespace abi;

class Entity
{
    static uint32_t counter;

public:
    using base_t = Entity;  // absolute base pattern
    using hash_type = utils::hash_type;
    using id_type = quint32;

protected:
    id_type id;

    struct NonIncrementFlag {};

    Entity();
    Entity(NonIncrementFlag&&);
    Entity(const QStringList& represent);
    Entity(const QByteArray& represent);

public:
    virtual ~Entity() = default;

    constexpr hash_type hash() const;

    template <typename T, abi::Version V>
    friend struct abi::Writer;

    template <typename T, abi::Version V>
    friend struct abi::Reader;

    virtual QByteArray hexHeader() const;
    virtual QStringList strHeader() const;

    id_type getId() const;
};

#endif // ENTITY_H
