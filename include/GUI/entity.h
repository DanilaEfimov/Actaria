/**
 * Base class for a game entity.
 * Provides an interface for identification and serialization.
 * Derived classes: Scene, Dialog, Trigger, and other game objects.
 */


#ifndef ENTITY_H
#define ENTITY_H

#include <QString>

class Entity
{
    QString name;
    int id;

    static int count;

public:
    Entity(const QString &name);
    virtual ~Entity();

    QString getName() const;
    int getId() const;

    virtual QString serialize() const = 0;
    virtual void deserialize(const QString &data) = 0;
    virtual size_t typeHash() const noexcept;

    bool operator<(const Entity& other) const;
    bool operator>(const Entity& other) const;

};

#endif // ENTITY_H
