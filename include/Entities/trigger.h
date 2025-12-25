#ifndef TRIGGER_H
#define TRIGGER_H

#include "Entities/contextvar.h"

class Trigger : public ContextVar
{
public:
    using value_type = bool;

protected:
    value_type value;

public:
    Trigger() = delete;
    Trigger(value_type value, const QString& name);
    Trigger(const QStringList& represent);
    Trigger(const QByteArray& represent);

    virtual ~Trigger() = default;

    value_type getValue() const;
    void setValue(value_type value) noexcept;

    operator bool() const noexcept;
};

#endif // TRIGGER_H
