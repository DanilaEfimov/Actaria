#include "Entities/nonplayercharacter.h"


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
    QDataStream in(data);
    abi::read<NonPlayerCharacter, EngineInfo::defaultVersion>(in, *this);
}

NonPlayerCharacter::NonPlayerCharacter(StringListCursor &data)
    : Character(), description()
{
    abi::read<NonPlayerCharacter, EngineInfo::defaultVersion>(data, *this);
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
