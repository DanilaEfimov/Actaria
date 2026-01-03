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
 * @param name
 */
void Character::setName(const QString &name)
{
    this->name = name;
}

/**
 * @brief Character::getMood
 * @return actual mood of a person
 */
Mood Character::getMood() const noexcept
{
    return this->mood;
}

/**
 * @brief Character::setMood
 * @param mood
 */
void Character::setMood(Mood mood)
{
    this->mood = mood;
}
