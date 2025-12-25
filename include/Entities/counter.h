#ifndef COUNTER_H
#define COUNTER_H

#include "Entities/contextvar.h"

class Counter : public ContextVar
{
public:
    using value_type = int32_t;

protected:
    value_type value;

public:
    Counter() = delete;
    Counter(value_type value, const QString& name);
    Counter(const QStringList& represent);
    Counter(const QByteArray& represent);

    value_type getValue() const;
    void setValue(value_type value) noexcept;

    operator int() const noexcept;
};

#endif // COUNTER_H
