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

/**
 * @brief Character::Character
 *
 * @param data
 */
Character::Character(const QByteArray &data)
    : Entity(NonIncrementFlag{})
{
    this->deserialize(data);
}

/**
 * @brief Character::Character
 *
 * @param data
 */
Character::Character(const QStringList &data)
    : Entity(NonIncrementFlag{})
{
    this->fromString(data);
}

/**
 * @brief Character::minimumSize
 *
 * @return minimum required size of QByteArray to deserialize hex dump
 */
quint32 Character::minimumSize() const
{
    return minimumQStringSize + sizeof(Mood) + this->Entity::minimumSize();
}

/**
 * @brief Character::minimumStrings
 *
 * @return minimum required count of strings to spell object
 */
quint32 Character::minimumStrings() const
{
    return fieldCount + this->Entity::minimumStrings();
}

/**
 * @brief Character::size
 *
 * @return actual size of Character
 */
size_t Character::size() const
{
    return QStringHexSize(this->name) + this->Entity::size();
}

/**
 * @brief Character::serialize
 *
 * @return hex dump of Character
 */
QByteArray Character::serialize() const
{
    QByteArray ret;
    QDataStream out(&ret, QDataStream::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    out << static_cast<QString>(this->name);
    out << static_cast<int>(this->mood);

    QByteArray arr = this->Entity::serialize();
    out.writeRawData(arr.constData(), arr.size());

    return ret;
}

/**
 * @brief Character::deserialize
 *
 * @param data
 */
void Character::deserialize(const QByteArray& data)
{
    if(data.size() < this->Character::minimumSize()){
        qWarning("Counter::deserialize: data too small");
        return;
    }

    QBuffer buffer;
    buffer.setData(data);
    buffer.open(QBuffer::ReadOnly);

    QDataStream in(&buffer);
    in.setVersion(QDataStream::Qt_6_5);

    in >> this->name >> this->mood;

    quint64 pos = buffer.pos();
    this->Entity::deserialize(data.mid(pos));
}

/**
 * @brief Character::represent
 *
 * @return readable representation of object
 */
QString Character::represent() const
{
    return QStringList{
        this->name,
        QString::number(static_cast<int>(this->mood)),
        this->Entity::represent()
    }.join(separator);
}

/**
 * @brief Character::fromString
 *
 * @param data
 */
void Character::fromString(const QStringList& data)
{
    if(data.size() < this->Character::minimumStrings()){
        qWarning("Character::fromString: data too small");
        return;
    }

    this->name = data[0];
    bool ok = false;
    this->mood = static_cast<Mood>(data[1].toInt(&ok));
    if(!ok){
        qWarning("Character::fromString: failed to parse the mood");
    }

    this->Entity::fromString(data.mid(fieldCount));
}
