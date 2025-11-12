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
    int id;

    static int counter;

public:

    Entity();
    virtual ~Entity() = default;

    virtual uint64_t hash() const;

    virtual size_t size() const = 0;
    virtual QByteArray serialize() const = 0;
    virtual void deserialize(const QByteArray&) = 0;

    virtual QString represent() const = 0;
    virtual void fromString(const QString&) = 0;

    int getId() const;

};

#endif // ENTITY_H
