#include "Entities/nonplayercharacter.h"

namespace {
    constexpr const char* typeName = "NonPlayerCharacter";
    constexpr const int fieldCount = 1;
}

/**
 * @brief NonPlayerCharacter::NonPlayerCharacter
 */
NonPlayerCharacter::NonPlayerCharacter()
    : Character(), description() {}

/**
 * @brief NonPlayerCharacter::NonPlayerCharacter
 * @param name
 * @param mood
 */
NonPlayerCharacter::NonPlayerCharacter(const QString &name, Mood mood)
    : Character(name, mood), description() {}

/**
 * @brief NonPlayerCharacter::NonPlayerCharacter
 * @param data
 */
NonPlayerCharacter::NonPlayerCharacter(const QByteArray &data)
    : Character(), description()
{
}

/**
 * @brief NonPlayerCharacter::setDescription
 * @param description
 */
void NonPlayerCharacter::setDescription(const QString &description)
{
    this->description = description;
}

/**
 * @brief NonPlayerCharacter::getDescription
 * @return
 */
QString NonPlayerCharacter::getDescription() const noexcept
{
    return this->description;
}

QByteArray NonPlayerCharacter::hexHeader() const
{

}

QStringList NonPlayerCharacter::strHeader() const
{

}
