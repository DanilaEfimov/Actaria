#ifndef NAMEVAR_H
#define NAMEVAR_H

#include "Entities/contextvar.h"

class NameVar : public ContextVar
{
    ACT_SERIALIZABLE

public:
    using base_t = ContextVar;
    using value_type = QString;
    static constexpr VarType contains = VarType::Name;

protected:
    value_type value;

public:
#ifndef ACTARIA_TEST
    NameVar() = delete;
#else
    NameVar() = default;
#endif
    NameVar(value_type value, const QString& name);

    virtual VarType type() const override;

    virtual ContextValue getValue() const override;
    virtual void setValue(ContextValue value) noexcept override;

    operator QString() const noexcept;
};

#include "namevar.ser"

#endif // NAMEVAR_H
