#include "Entities/trigger.h"
#include <QByteArray>
#include <QDataStream>
#include <QBuffer>
#include <QVariant>


namespace {
    constexpr const char* typeName = "Trigger";
};

quint32 Trigger::minimumSize() const
{
    return sizeof(hash_type) + sizeof(value_type) + this->ContextVar::minimumSize();
}

Trigger::Trigger()
: ContextVar(), value(false) {}

Trigger::Trigger(value_type value, const QString &name)
    : ContextVar(name), value(value) {}

Trigger::Trigger(const QStringList &represent)
    : ContextVar()
{
    this->fromString(represent);
}

Trigger::value_type Trigger::getValue() const
{
    return this->value;
}

void Trigger::setValue(value_type value) noexcept
{
    this->value = value;
}

Trigger::operator bool() const noexcept
{
    return this->value;
}

Entity::hash_type Trigger::hash() const
{
    return utils::fnv1a_64(typeName);
}

size_t Trigger::size() const
{
    // >= 25 bytes (without QChars)
    // [hash code][value][name][entity hash code][id]
    return sizeof(utils::hash_type)
           + sizeof(value_type)
           + this->ContextVar::size();
}

QByteArray Trigger::serialize() const
{
    /**
     * [hash code][value][ContextVar]
     * returns byte representation of Trigger.
     */
    QByteArray ret;
    QDataStream out(&ret, QDataStream::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    out << static_cast<hash_type>(this->hash())
        << static_cast<value_type>(this->value);

    QByteArray arr = this->ContextVar::serialize();
    out.writeRawData(arr.constData(), arr.size());

    return ret;
}

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

    in.skipRawData(sizeof(hash_type));

    in >> this->value;

    quint64 pos = buffer.pos();
    this->ContextVar::deserialize(data.mid(pos));
}

QString Trigger::represent() const
{
    // Example: "Trigger::1::checkpoint::Entity::23"
    return QStringList{
        typeName,
        QString::number(this->value),
        this->ContextVar::represent()
    }.join(separator);
}

void Trigger::fromString(const QStringList &data)
{
    if(data.size() < 5){
        qWarning("Trigger::fromString: data too small");
        return;
    }

    bool ok;
    this->value = static_cast<bool>(data[1].toInt(&ok));
    if(!ok){
        qWarning("Trigger::Failed to parse entity id");
    }

    this->ContextVar::fromString(data.mid(2));
}
