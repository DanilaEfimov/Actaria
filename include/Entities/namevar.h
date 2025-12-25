#ifndef NAMEVAR_H
#define NAMEVAR_H

#include "Entities/contextvar.h"

class NameVar : public ContextVar
{
public:
    using value_type = QString;

protected:
    value_type value;

public:
    NameVar() = delete;
    NameVar(value_type value, const QString& name);
    NameVar(const QStringList& represent);
    NameVar(const QByteArray& represent);

    value_type getValue() const;
    void setValue(value_type value) noexcept;

    operator QString() const noexcept;

    virtual QByteArray hexHeader() const override;
    virtual QStringList strHeader() const override;
};

#endif // NAMEVAR_H
