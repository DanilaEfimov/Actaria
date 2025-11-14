#include "Entities/counter.h"
#include <QBuffer>
#include <QDataStream>

namespace {
    constexpr const char* typeName = "Counter";
}

/**
 * @brief Counter::Counter
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
 * @return
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
 * @return
 */
quint32 Counter::minimumSize() const
{
    return sizeof(value_type) + this->ContextVar::minimumSize();
}

/**
 * @brief Counter::hash
 *
 * @return
 */
Entity::hash_type Counter::hash() const
{
    return utils::fnv1a_64(typeName);
}

/**
 * @brief Counter::size
 *
 * @return
 */
size_t Counter::size() const
{
    return sizeof(value_type) + this->ContextVar::size();
}

/**
 * @brief Counter::serialize
 *
 * @param isPostfix
 *
 * @return
 */
QByteArray Counter::serialize(bool isPrefix) const
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
 * @brief Counter::deserialize
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
 * @return
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
 */
void Counter::fromString(const QStringList &data)
{
    if(data.size() < 5){
        qWarning("Counter::fromString: data too small");
        return;
    }

    bool ok;
    this->value = static_cast<value_type>(data[1].toInt(&ok));
    if(!ok){
        qWarning("Counter::Failed to parse entity id");
    }

    this->ContextVar::fromString(data.mid(2));
}
