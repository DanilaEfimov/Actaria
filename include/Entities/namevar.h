#ifndef NAMEVAR_H
#define NAMEVAR_H

#include "Entities/contextvar.h"

class NameVar : public ContextVar
{
protected:
    using value_type = QString;

    value_type value;

    quint32 minimumSize() const override;
    quint32 minimumStrings() const override;

public:
    NameVar() = delete;
    NameVar(value_type value, const QString& name);
    NameVar(const QStringList& represent);
    NameVar(const QByteArray& represent);

    value_type getValue() const;
    void setValue(value_type value) noexcept;

    operator QString() const noexcept;

    // Entity interface
    hash_type hash() const override;
    size_t size() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &) override;
    QString represent() const override;
    void fromString(const QStringList &) override;
};

#endif // NAMEVAR_H
