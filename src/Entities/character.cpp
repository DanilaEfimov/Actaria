#include "Entities/character.h"
#include <QBuffer>


/**
 * @brief Character::Character
 */
Character::Character()
    : Entity(NonIncrementFlag{})
{}

/**
 * @brief Character::Character
 * @param name
 * @param mood
 */
Character::Character(const QString &name, Mood mood)
    : Entity(), name(name), mood(mood)
{}

/**
 * @brief Character::getName
 * @return name of character
 */
QString Character::getName() const noexcept
{
    return this->name;
}

/**
 * @brief Character::setName
 */
void Character::setName(QString name)
{
    this->name = name;
}
