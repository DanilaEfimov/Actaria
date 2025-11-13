#include "Entities/contextvar.h"


ContextVar::ContextVar()
    : Entity(), name() {}

ContextVar::ContextVar(const QStringList& represent)
    : Entity(represent) {}

ContextVar::ContextVar(const QByteArray& represent)
    : Entity(represent) {}

size_t ContextVar::size() const
{
    // postfix for direvers
    // ...[name][entity hash code][id]
    return sizeof(quint32)  // length of name in QChars
           + this->name.size() * sizeof(QChar)
           +this->Entity::size();
}

QString ContextVar::getName() const
{
    return this->name;
}

void ContextVar::setName(const QString &name) noexcept
{
    this->name = name;
}

