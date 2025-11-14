#include "Entities/trigger.h"
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>
#include <QVariant>

namespace {
    constexpr const char* typeName = "Trigger";
};

/**
 * @brief Trigger::minimumSize
 *
 * @return
 */
quint32 Trigger::minimumSize() const
{
    return sizeof(value_type) + this->ContextVar::minimumSize();
}

/**
 * @brief Trigger::Trigger
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
 * @return
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
 * @return
 */
Entity::hash_type Trigger::hash() const
{
    return utils::fnv1a_64(typeName);
}

/**
 * @brief Trigger::size
 *
 * @return
 */
size_t Trigger::size() const
{
    return sizeof(value_type)
           + this->ContextVar::size();
}

/**
 * @brief Trigger::serialize
 *
 * @param isPrefix
 *
 * @return
 */
QByteArray Trigger::serialize(bool isPrefix) const
{
    QByteArray ret;
    QDataStream out(&ret, QDataStream::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    if(!isPrefix)
        out << static_cast<hash_type>(this->hash());
    out << static_cast<value_type>(this->value);

    QByteArray arr = this->ContextVar::serialize(true);
    out.writeRawData(arr.constData(), arr.size());

    return ret;
}

/**
 * @brief Trigger::deserialize
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
 * @return
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
 * @param data
 */
void Trigger::fromString(const QStringList &data)
{
    if(data.size() < 5){
        qWarning("Trigger::fromString: data too small");
        return;
    }

    bool ok;
    this->value = static_cast<value_type>(data[1].toInt(&ok));
    if(!ok){
        qWarning("Trigger::Failed to parse entity id");
    }

    this->ContextVar::fromString(data.mid(2));
}
