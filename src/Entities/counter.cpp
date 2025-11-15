#include "Entities/counter.h"
#include <QBuffer>
#include <QDataStream>

namespace {
    constexpr const char* typeName = "Counter";
    constexpr const int fieldCount = 2;
}

/**
 * @brief Counter::Counter
 *
 * Normal constructor for context counter.
 *
 * @param value
 *
 * @param name
 */
Counter::Counter(value_type value, const QString &name)
    : ContextVar(name), value(value) {}

/**
 * @brief Counter::Counter
 *
 * Non global entity counter increment.
 * Hex parse-based constructor.
 *
 * @param represent
 */
Counter::Counter(const QStringList &represent)
    : ContextVar()
{
    this->fromString(represent);
}

/**
 * @brief Counter::Counter
 *
 * Non global entity counter increment.
 * QString parse-based constructor.
 *
 * @param represent
 */
Counter::Counter(const QByteArray &represent)
    : ContextVar()
{
    this->deserialize(represent);
}

/**
 * @brief Counter::getValue
 *
 * @return trigger-counter
 */
Counter::value_type Counter::getValue() const
{
    return this->value;
}

/**
 * @brief Counter::setValue
 *
 * @param value
 */
void Counter::setValue(value_type value) noexcept
{
    this->value = value;
}

/**
 * @brief Counter::operator int
 */
Counter::operator int() const noexcept
{
    return this->value;
}

/**
 * @brief Counter::minimumSize
 *
 * @return minimum required size for hex-dump
 */
quint32 Counter::minimumSize() const
{
    return sizeof(value_type) + this->ContextVar::minimumSize();
}

/**
 * @brief Counter::minimumStrings
 *
 * @return count of required strings in representation
 */
quint32 Counter::minimumStrings() const
{
    return fieldCount + this->ContextVar::minimumStrings();
}

/**
 * @brief Counter::hash
 *
 * @return fnv-1a hash of typeName string
 */
Entity::hash_type Counter::hash() const
{
    return utils::fnv1a_64(typeName);
}

/**
 * @brief Counter::size
 *
 * @return actual size of object in bytes
 */
size_t Counter::size() const
{
    return sizeof(value_type) + this->ContextVar::size();
}

/**
 * @brief Counter::serialize
 *
 * @param isPostfix - true if called by deriver
 *
 * @return hex-dump of object
 */
QByteArray Counter::serialize() const
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
 * @brief Counter::deserialize
 *
 * Parse raw bytes in lineral order.
 *
 * @param data
 */
void Counter::deserialize(const QByteArray& data)
{
    if(data.size() < this->Counter::minimumSize()){
        qWarning("Counter::deserialize: data too small");
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
 * @brief Counter::represent
 *
 * @return Readable QString presentation
 */
QString Counter::represent() const
{
    return QStringList{
        typeName,
        QString::number(this->value),
        this->ContextVar::represent()
    }.join(separator);
}

/**
 * @brief Counter::fromString
 *
 * Parse QString in lineral order with typeNmae skipping.
 *
 * @param data
 */
void Counter::fromString(const QStringList &data)
{
    if(data.size() < this->Counter::minimumStrings()){
        qWarning("Counter::fromString: data too small");
        return;
    }

    bool ok;
    this->value = static_cast<value_type>(data[1].toInt(&ok));
    if(!ok){
        qWarning("Counter::Failed to parse entity id");
    }

    this->ContextVar::fromString(data.mid(fieldCount));
}
