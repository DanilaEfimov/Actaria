#ifndef TRIGGER_H
#define TRIGGER_H

#include "Entities/contextvar.h"

class Trigger : public ContextVar
{
protected:
    using value_type = bool;

    value_type value;

    quint32 minimumSize() const override;

public:
    Trigger();
    Trigger(value_type value, const QString& name);
    Trigger(const QStringList& represent);
    Trigger(const QByteArray& represent);

    value_type getValue() const;
    void setValue(value_type value) noexcept;

    operator bool() const noexcept;

    // Entity interface
    hash_type hash() const override;
    size_t size() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &) override;
    QString represent() const override;
    void fromString(const QStringList &data) override;
};

#endif // TRIGGER_H
