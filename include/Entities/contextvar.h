/**
 * Interface for context variables: counters, triggers and names
*/

#ifndef CONTEXTVAR_H
#define CONTEXTVAR_H

#include "Entities/entity.h"

enum class VarType {
    Unknown = -1,
    Counter,        // int
    Trigger,        // bool
    Name            // QString
};

class ContextVar : public Entity
{
    ACT_SERIALIZABLE

public:
    using base_t = Entity;
    using ContextValue = std::variant<int, bool, QString>;
    static constexpr VarType contains = VarType::Unknown;

protected:
    QString name;

    ContextVar(const QString& name);

public:
    ContextVar();
    virtual ~ContextVar() = default;

    virtual hash_type hash() const override;

    virtual VarType type() const = 0;

    QString getName() const;
    void setName(const QString& name) noexcept;

    virtual ContextValue getValue() const = 0;
    virtual void setValue(ContextValue value) = 0;
};

#endif // CONTEXTVAR_H
