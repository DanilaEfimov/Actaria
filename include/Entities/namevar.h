#ifndef NAMEVAR_H
#define NAMEVAR_H

#include "Entities/contextvar.h"

class NameVar : public ContextVar
{
    ACT_SERIALIZABLE

public:
    using value_type = QString;

protected:
    value_type value;

public:
    NameVar() = delete;
    NameVar(value_type value, const QString& name);

    value_type getValue() const;
    void setValue(value_type value) noexcept;

    operator QString() const noexcept;
};

#endif // NAMEVAR_H
