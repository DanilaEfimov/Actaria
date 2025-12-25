/**
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

    enum EntityAbi {
        IdField,    // id_type
    };

};  // namespace abi

using namespace abi;

class Entity
{
    static uint32_t counter;

public:
    using hash_type = utils::hash_type;
    using id_type = quint32;

    // using for human-readable serializing
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

    template <typename T, abi::Version V>
    friend struct abi::Writer;

    template <typename T, abi::Version V>
    friend struct abi::Reader;

    // returns serialized object size in bytes
    [[deprecated("Use abi::write/read instead")]]
    virtual size_t size() const;
    [[deprecated("Use abi::write/read instead")]]
    virtual QByteArray serialize() const;
    [[deprecated("Use abi::write/read instead")]]
    virtual void deserialize(const QByteArray&);

    [[deprecated("Use abi::write/read instead")]]
    virtual QString represent() const;
    [[deprecated("Use abi::write/read instead")]]
    virtual void fromString(const QStringList&);

    id_type getId() const;
};

#endif // ENTITY_H
