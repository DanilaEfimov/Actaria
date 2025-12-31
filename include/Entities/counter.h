#ifndef COUNTER_H
#define COUNTER_H

#include "Entities/contextvar.h"

class Counter : public ContextVar
{
    ACT_SERIALIZABLE

public:
    using base_t = ContextVar;
    using value_type = int32_t;

protected:
    value_type value;

public:
#ifndef ACTARIA_TEST
    Counter() = delete;
#else
    Counter() = default;
#endif
    Counter(value_type value, const QString& name);

    value_type getValue() const;
    void setValue(value_type value) noexcept;

    operator int() const noexcept;
};

#include "counter.ser"

#endif // COUNTER_H
