#ifndef COUNTER_H
#define COUNTER_H

#include "Entities/contextvar.h"

class Counter : public ContextVar
{
    ACT_SERIALIZABLE

public:
    using base_t = ContextVar;
    using value_type = int32_t;
    static constexpr VarType contains = VarType::Counter;

protected:
    value_type value;

public:
#ifndef ACTARIA_TEST
    Counter() = delete;
#else
    Counter() = default;
#endif
    Counter(value_type value, const QString& name);

    virtual hash_type hash() const override;

    virtual VarType type() const override;

    virtual ContextValue getValue() const override;
    virtual void setValue(ContextValue value) noexcept override;

    operator int() const noexcept;
};

#endif // COUNTER_H
