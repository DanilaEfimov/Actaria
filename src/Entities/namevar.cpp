#include "Entities/namevar.h"
#include <QBuffer>
#include <QDataStream>

namespace {
    constexpr const char* typeName = "NameVar";
    constexpr const int fieldCount = 2;
}

NameVar::NameVar(value_type value, const QString &name)
    : ContextVar(name), value(value) {}

NameVar::NameVar(const QStringList &represent)
    : ContextVar()
{
    this->fromString(represent);
}

NameVar::NameVar(const QByteArray &represent)
    : ContextVar()
{
    this->deserialize(represent);
}

quint32 NameVar::minimumSize() const
{
    return sizeof(quint32) + this->value.size() * sizeof(QChar) + this->ContextVar::minimumSize();
}

quint32 NameVar::minimumStrings() const
{
    return fieldCount + this->ContextVar::minimumStrings();
}

Entity::hash_type NameVar::hash() const
{
    return utils::fnv1a_64(typeName);
}

size_t NameVar::size() const
{
    return sizeof(quint32) + this->value.size() * sizeof(QChar) + this->ContextVar::size();
}

/**
 * @brief NameVar::serialize
 *
 * @param isPostfix - true if called by deriver
 *
 * @return hex-dump of object
 */
QByteArray NameVar::serialize() const
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
 * @brief NameVar::deserialize
 *
 * Parse raw bytes in lineral order.
 *
 * @param data
 */
void NameVar::deserialize(const QByteArray& data)
{
    if(data.size() < this->NameVar::minimumSize()){
        qWarning("NameVar::deserialize: data too small");
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
 * @brief NameVar::represent
 *
 * @return Readable QString presentation
 */
QString NameVar::represent() const
{
    return QStringList{
        typeName,
        this->value,
        this->ContextVar::represent()
    }.join(separator);
}

/**
 * @brief NameVar::fromString
 *
 * Parse QString in lineral order with typeName skipping.
 *
 * @param data
 */
void NameVar::fromString(const QStringList &data)
{
    if(data.size() < this->NameVar::minimumStrings()){
        qWarning("NameVar::fromString: data too small");
        return;
    }

    bool ok;
    this->value = static_cast<value_type>(data[1]);
    if(!ok){
        qWarning("NameVar::Failed to parse entity id");
    }

    this->ContextVar::fromString(data.mid(fieldCount));
}
