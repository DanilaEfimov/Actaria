#ifndef COUNTER_H
#define COUNTER_H

#include "Entities/contextvar.h"

class Counter : public ContextVar
{
protected:
    using value_type = int32_t;

    value_type value;

    quint32 minimumSize() const override;

public:
    Counter() = delete;
    Counter(value_type value, const QString& name);
    Counter(const QStringList& represent);
    Counter(const QByteArray& represent);

    value_type getValue() const;
    void setValue(value_type value) noexcept;

    operator int() const noexcept;

    // Entity interface
    hash_type hash() const override;
    size_t size() const override;
    QByteArray serialize(bool isPostfix = false) const override;
    void deserialize(const QByteArray &) override;
    QString represent() const override;
    void fromString(const QStringList &) override;
};

#endif // COUNTER_H
