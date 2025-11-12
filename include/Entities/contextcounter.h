#ifndef CONTEXTCOUNTER_H
#define CONTEXTCOUNTER_H

#include "Entities/contextvar.h"

class ContextCounter : public ContextVar
{
public:
    using value_type = int32_t;

protected:
    value_type value;

public:
    ContextCounter(const QString& name, value_type value);
    virtual ~ContextCounter() = default;

    value_type getValue() const;

    // Entity interface
    hash_type hash() const override;
    size_t size() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray& data) override;
    QString represent() const override;
    void fromString(const QString& data) override;
};

#endif // CONTEXTCOUNTER_H
