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

    Entity();
    Entity(const QStringList& represent);
    Entity(const QByteArray& represent);

public:
    virtual ~Entity() = default;

    virtual hash_type hash() const;

    // returns serialized object size in bytes
    virtual size_t size() const;
    virtual QByteArray serialize() const;
    virtual void deserialize(const QByteArray&);

    virtual QString represent() const;
    virtual void fromString(const QStringList& data);

    id_type getId() const;

};

#endif // ENTITY_H
