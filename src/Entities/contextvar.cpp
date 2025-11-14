#include "Entities/contextvar.h"
#include <QBuffer>


ContextVar::ContextVar()
    : Entity(NonIncrementFlag{}), name() {}

ContextVar::ContextVar(const QString &name)
    : Entity(), name(name) {}

ContextVar::ContextVar(const QStringList& represent)
    : Entity(NonIncrementFlag{})
{
    /**
     * It is assumed here that the id will be read from
     * the provided object representation,
     * so a dummy parent constructor is used.
    */
    this->fromString(represent);
}

ContextVar::ContextVar(const QByteArray& represent)
    : Entity(NonIncrementFlag{})
{
    this->deserialize(represent);
}

size_t ContextVar::size() const
{
    return sizeof(quint32)  // length of name in QChars
           + this->name.size() * sizeof(QChar)
           + this->Entity::size();
}

quint32 ContextVar::minimumSize() const
{
    return sizeof(QChar) + this->Entity::minimumSize();
}

QByteArray ContextVar::serialize(bool isPrefix) const
{
    QByteArray ret;
    QDataStream out(&ret, QDataStream::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);

    out << static_cast<QString>(this->name);

    QByteArray arr = this->Entity::serialize(true);
    out.writeRawData(arr.constData(), arr.size());

    return ret;
}

void ContextVar::deserialize(const QByteArray &data)
{
    if (data.size() < this->ContextVar::minimumSize()) {
        qWarning("ContextVar::deserialize: data too small");
        return;
    }

    QBuffer buffer;
    buffer.setData(data);
    buffer.open(QIODevice::ReadOnly);

    QDataStream in(&buffer);
    in.setVersion(QDataStream::Qt_6_5);

    in >> name; // QString
    quint64 pos = buffer.pos();
    this->Entity::deserialize(data.mid(pos));
}


QString ContextVar::represent() const
{
    return this->name + separator + this->Entity::represent();
}

void ContextVar::fromString(const QStringList &data)
{
    if(data.size() < 3){
        qWarning("ContextVar::fromString: data too small");
        return;
    }

    this->name = data[0];
    this->Entity::fromString(data.mid(1));
}

QString ContextVar::getName() const
{
    return this->name;
}

void ContextVar::setName(const QString &name) noexcept
{
    this->name = name;
}
