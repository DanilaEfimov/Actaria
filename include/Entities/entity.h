/**
 * Base class for a game entity.
 * Provides an interface for identification and serialization.
 * Derived classes: Scene, Dialog, Trigger, and other game objects.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "utils.h"
#include <QString>
#include <QByteArray>

class Entity
{
    static uint32_t counter;

public:
    using hash_type = utils::hash_type;
    using id_type = uint32_t;

    static constexpr const char* separator = "::";

protected:
    id_type id;

    struct NonIncrementFlag {};

    Entity();
    Entity(NonIncrementFlag&&);
    Entity(const QStringList& represent);
    Entity(const QByteArray& represent);

    virtual quint32 minimumSize() const;
    virtual quint32 minimumStrings() const;

public:
    virtual ~Entity() = default;

    virtual hash_type hash() const;

    // returns serialized object size in bytes
    virtual size_t size() const;
    virtual QByteArray serialize() const;
    virtual void deserialize(const QByteArray&);

    virtual QString represent() const;
    virtual void fromString(const QStringList&);

    id_type getId() const;

};

#endif // ENTITY_H
