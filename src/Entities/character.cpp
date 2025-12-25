#include "Entities/character.h"
#include <QBuffer>

namespace {
    constexpr const int fieldCount = 2;
}

Character::Character()
    : Entity(NonIncrementFlag{}) {}

/**
 * @brief Character::Character
 *
 * @param name
 *
 * @param mood
 */
Character::Character(const QString &name, Mood mood)
    : Entity(), name(name), mood(mood) {}

/**
 * @brief Character::getName
 *
 * @return
 */
QString Character::getName() const noexcept
{
    return this->name;
}

QByteArray Character::hexHeader() const
{

}

QStringList Character::strHeader() const
{

}

/**
 * @brief Character::Character
 *
 * @param data
 */
Character::Character(const QByteArray &data)
    : Entity(NonIncrementFlag{})
{
}

/**
 * @brief Character::Character
 *
 * @param data
 */
Character::Character(const QStringList &data)
    : Entity(NonIncrementFlag{})
{
}
