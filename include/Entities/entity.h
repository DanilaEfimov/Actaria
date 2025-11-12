/**
 * Base class for a game entity.
 * Provides an interface for identification and serialization.
 * Derived classes: Scene, Dialog, Trigger, and other game objects.
 */


#ifndef ENTITY_H
#define ENTITY_H

#include <QString>
#include <QByteArray>

class Entity
{
    static int counter;

public:
    using size_type = uint64_t;
    using hash_type = uint64_t;
    using id_type = uint32_t;

protected:
    id_type id;

public:

    Entity();
    virtual ~Entity() = default;

    virtual hash_type hash() const = 0;

    // returns serialized object size in bytes
    virtual size_t size() const = 0;
    virtual QByteArray serialize() const = 0;
    virtual void deserialize(const QByteArray&) = 0;

    virtual QString represent() const = 0;
    virtual void fromString(const QString&) = 0;

    id_type getId() const;

};

#endif // ENTITY_H
