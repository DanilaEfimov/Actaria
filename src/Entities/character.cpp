#include "Entities/character.h"


Character::Character(const QString &name)
    : Entity()
{

}

Character::Character(const QStringList &represent)
{

}

Character::Character(const QByteArray &represent)
{

}

quint32 Character::minimumSize() const
{
}

quint32 Character::minimumStrings() const
{
}

Entity::hash_type Character::hash() const
{
}

size_t Character::size() const
{
}

QByteArray Character::serialize() const
{
}

void Character::deserialize(const QByteArray &)
{
}

QString Character::represent() const
{
}

void Character::fromString(const QStringList &)
{
}
