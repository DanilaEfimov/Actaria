#include "Entities/dialog.h"


namespace {
    constexpr const char* typeName = "Dialog";
};


Dialog::Dialog()
    : Entity() {}

quint32 Dialog::minimumSize() const
{
}

quint32 Dialog::minimumStrings() const
{
}

Entity::hash_type Dialog::hash() const
{
    return utils::fnv1a_64(typeName);
}

size_t Dialog::size() const
{
}

QByteArray Dialog::serialize() const
{
}

void Dialog::deserialize(const QByteArray &)
{
}

QString Dialog::represent() const
{
}

void Dialog::fromString(const QStringList &)
{
}
