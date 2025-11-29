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
    this->deserialize(data);
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

/**
 * @brief NonPlayerCharacter::minimumSize
 * @return
 */
quint32 NonPlayerCharacter::minimumSize() const
{
    return minimumQStringSize + this->Character::minimumSize();
}

/**
 * @brief NonPlayerCharacter::minimumStrings
 * @return
 */
quint32 NonPlayerCharacter::minimumStrings() const
{
    return fieldCount + this->Character::minimumStrings();
}

/**
 * @brief NonPlayerCharacter::hash
 * @return
 */
Entity::hash_type NonPlayerCharacter::hash() const
{
    return utils::fnv1a_64(typeName);
}

/**
 * @brief NonPlayerCharacter::size
 * @return
 */
size_t NonPlayerCharacter::size() const
{
    return QStringHexSize(this->description) + this->Character::size();
}

/**
 * @brief NonPlayerCharacter::serialize
 * @return
 */
QByteArray NonPlayerCharacter::serialize() const
{
}

/**
 * @brief NonPlayerCharacter::deserialize
 * @param data
 */
void NonPlayerCharacter::deserialize(const QByteArray& data)
{
}

/**
 * @brief NonPlayerCharacter::represent
 * @return
 */
QString NonPlayerCharacter::represent() const
{
}

/**
 * @brief NonPlayerCharacter::fromString
 */
void NonPlayerCharacter::fromString(const QStringList& data)
{
}
