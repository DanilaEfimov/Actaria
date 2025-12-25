#ifndef TRIGGER_H
#define TRIGGER_H

#include "Entities/contextvar.h"

class Trigger : public ContextVar
{
    ACT_SERIALIZABLE

public:
    using base_t = ContextVar;
    using value_type = bool;

protected:
    value_type value;

public:
    Trigger() = delete;
    Trigger(value_type value, const QString& name);

    virtual ~Trigger() = default;

    value_type getValue() const;
    void setValue(value_type value) noexcept;

    operator bool() const noexcept;
};

#endif // TRIGGER_H
