#include "Entities/trigger.h"

namespace {
    constexpr const char* typeName = "Trigger";
};

Trigger::Trigger()
    : ContextVar(), value(false) {}

Trigger::value_type Trigger::getValue() const
{
    return this->value;
}

void Trigger::setValue(value_type value) noexcept
{
    this->value = value;
}

Trigger::operator bool() const noexcept
{
    return this->value;
}

Entity::hash_type Trigger::hash() const
{
    return utils::fnv1a_64(typeName);
}

size_t Trigger::size() const
{
    // >= 25 bytes (without QChars)
    // [hash code][value][name][entity hash code][id]
    return sizeof(utils::hash_type)
           + sizeof(value_type)
           + this->ContextVar::size();
}

QByteArray Trigger::serialize() const
{
}

void Trigger::deserialize(const QByteArray &)
{
}

QString Trigger::represent() const
{
}

void Trigger::fromString(const QStringList &data)
{
}
