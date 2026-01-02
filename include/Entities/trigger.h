#ifndef TRIGGER_H
#define TRIGGER_H

#include "Entities/contextvar.h"

#define TRUE_S "true"
#define FALSE_S "false"

class Trigger : public ContextVar
{
    ACT_SERIALIZABLE

public:
    using base_t = ContextVar;
    using value_type = bool;
    static constexpr VarType contains = VarType::Trigger;

protected:
    value_type value;

public:
#ifndef ACTARIA_TEST
    Trigger() = delete;
#else
    Trigger() = default;
#endif
    Trigger(value_type value, const QString& name);

    virtual ~Trigger() = default;

    virtual VarType type() const override;

    virtual ContextValue getValue() const override;
    virtual void setValue(ContextValue value) noexcept override;

    operator bool() const noexcept;
};

#include "trigger.ser"

#endif // TRIGGER_H
