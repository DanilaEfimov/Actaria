#include "Entities/trigger.h"
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>
#include <QVariant>

namespace {
    constexpr const char* typeName = "Trigger";
    constexpr const int fieldCount = 2;
};

/**
 * @brief Trigger::minimumSize
 *
 * @return minimum required size for hex-dump
 */
quint32 Trigger::minimumSize() const
{
    return sizeof(value_type) + this->ContextVar::minimumSize();
}

/**
 * @brief Trigger::minimumStrings
 *
 * @return count of required strings in representation
 */
quint32 Trigger::minimumStrings() const
{
    return fieldCount + this->ContextVar::minimumStrings();
}

/**
 * @brief Trigger::Trigger
 *
 * Normal constructor for context counter.
 *
 * @param value
 *
 * @param name
 */
Trigger::Trigger(value_type value, const QString &name)
    : ContextVar(name), value(value) {}

/**
 * @brief Trigger::Trigger
 *
 * Non global entity counter increment.
 * Hex parse-based constructor.
 *
 * @param represent
 */
Trigger::Trigger(const QStringList &represent)
    : ContextVar()
{
    this->fromString(represent);
}

/**
 * @brief Trigger::Trigger
 *
 * Non global entity counter increment.
 * QString parse-based constructor.
 *
 * @param represent
 */
Trigger::Trigger(const QByteArray &represent)
    : ContextVar()
{
    this->deserialize(represent);
}

/**
 * @brief Trigger::getValue
 *
 * @return trigger-value
 */
Trigger::value_type Trigger::getValue() const
{
    return this->value;
}

/**
 * @brief Trigger::setValue
 *
 * @param value
 */
void Trigger::setValue(value_type value) noexcept
{
    this->value = value;
}

/**
 * @brief Trigger::operator bool
 */
Trigger::operator bool() const noexcept
{
    return this->value;
}

/**
 * @brief Trigger::hash
 *
 * @return fnv-1a hash of typeName string
 */
Entity::hash_type Trigger::hash() const
{
    return utils::fnv1a_64(typeName);
}

/**
 * @brief Trigger::size
 *
 * @return actual size of object in bytes
 */
size_t Trigger::size() const
{
    return sizeof(value_type)
           + this->ContextVar::size();
}

/**
 * @brief Trigger::serialize
 *
 * @param isPostfix - true if called by deriver
 *
 * @return hex-dump of object
 */
QByteArray Trigger::serialize() const
{
    QByteArray ret;
    QDataStream out(&ret, QDataStream::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    out << static_cast<value_type>(this->value);

    QByteArray arr = this->ContextVar::serialize();
    out.writeRawData(arr.constData(), arr.size());

    return ret;
}

/**
 * @brief Trigger::deserialize
 *
 * Parse raw bytes in lineral order.
 *
 * @param data
 */
void Trigger::deserialize(const QByteArray& data)
{
    if(data.size() < this->Trigger::minimumSize()){
        qWarning("Trigger::deserialize: data too small");
        return;
    }

    QBuffer buffer;
    buffer.setData(data);
    buffer.open(QBuffer::ReadOnly);

    QDataStream in(&buffer);
    in.setVersion(QDataStream::Qt_6_5);

    in >> this->value;

    quint64 pos = buffer.pos();
    this->ContextVar::deserialize(data.mid(pos));
}

/**
 * @brief Trigger::represent
 *
 * @return Readable QString presentation
 */
QString Trigger::represent() const
{
    return QStringList{
        typeName,
        QString::number(this->value),
        this->ContextVar::represent()
    }.join(separator);
}

/**
 * @brief Trigger::fromString
 *
 * Parse QString in lineral order with typeName skipping.
 *
 * @param data
 */
void Trigger::fromString(const QStringList &data)
{
    if(data.size() < this->Trigger::minimumSize()){
        qWarning("Trigger::fromString: data too small");
        return;
    }

    bool ok;
    this->value = static_cast<value_type>(data[1].toInt(&ok));
    if(!ok){
        qWarning("Trigger::Failed to parse entity id");
    }

    this->ContextVar::fromString(data.mid(fieldCount));
}
