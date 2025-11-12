#include "Entities/contextcounter.h"
#include "utils.h"
#include <QIODevice>
#include <QBuffer>

namespace {
    constexpr const char* typeName = "ContextCounter";
    constexpr const char* separator = "::";
};


ContextCounter::ContextCounter(const QString &name, value_type value)
    : ContextVar(name), value(value) {}

ContextCounter::value_type ContextCounter::getValue() const
{
    return this->value;
}

ContextCounter::hash_type ContextCounter::hash() const
{
    return fnv1a_64(typeName, 14);
}

size_t ContextCounter::size() const
{
    // >= 20 bytes
    return sizeof(hash_type)
           + sizeof(id_type)
           + sizeof(value_type)
           + sizeof(quint32)    // length of context variable name
           + this->name.size() * sizeof(QChar); // raw UTF-16 chars
}

QByteArray ContextCounter::serialize() const
{
    /**
     * >= 20 bytes
     * [hash][id][value][name.size()...UTF-16 name]
     * [8 bytes][4 bytes][4 bytes][4 bytes+2*name.size() bytes]
    */
    QByteArray ret;
    QDataStream out(&ret, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    out << static_cast<hash_type>(this->hash())
        << static_cast<id_type>(this->id)
        << static_cast<value_type>(this->value)
        << static_cast<QString>(this->name);

    return ret;
}

void ContextCounter::deserialize(const QByteArray& data)
{
    /**
     * >= 20 bytes
     * [int id][int value][uint32_t name.size()...QString name]
     * [4 bytes][4 bytes][4 bytes+2*name.size() bytes]
    */
    QBuffer buffer(const_cast<QByteArray*>(&data));
    buffer.open(QIODevice::ReadOnly);

    QDataStream in(&buffer);
    in.setVersion(QDataStream::Qt_6_5);

    in.device()->seek(sizeof(uint64_t));
    id_type _id;
    value_type _value;
    QString _name;
    in >> _id >> _value >> _name;

    this->id = _id;
    this->value = _value;
    this->name = _name;
}

QString ContextCounter::represent() const
{
    QString typeFlag = QString::number(this->hash());
    QString idStr = QString::number(this->id);
    QString valueStr = QString::number(this->value);
    return QStringList{typeFlag, idStr, valueStr, this->name}.join(separator);
}

void ContextCounter::fromString(const QString& data)
{
    QStringList words = data.split(separator);
    this->id = static_cast<id_type>(words[1].toInt());
    this->value = static_cast<value_type>(words[2].toInt());
    this->name = words[3];
}
