#include "Entities/namevar.h"
#include <QBuffer>
#include <QDataStream>

namespace {
    constexpr const char* typeName = "NameVar";
    constexpr const int fieldCount = 2;
};

/**
 * @brief NameVar::NameVar
 *
 * @param value
 *
 * @param name
 */
NameVar::NameVar(value_type value, const QString &name)
    : ContextVar(name), value(value) {}

/**
 * @brief NameVar::NameVar
 *
 * @param represent
 */
NameVar::NameVar(const QStringList &represent)
    : ContextVar()
{
}

/**
 * @brief NameVar::NameVar
 *
 * @param represent
 */
NameVar::NameVar(const QByteArray &represent)
    : ContextVar()
{
}

NameVar::value_type NameVar::getValue() const
{

}

void NameVar::setValue(value_type value) noexcept
{

}

QByteArray NameVar::hexHeader() const
{

}

QStringList NameVar::strHeader() const
{

}
