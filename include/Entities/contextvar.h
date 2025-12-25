/**
 * Interface for context variables: counters, triggers and names
*/

#ifndef CONTEXTVAR_H
#define CONTEXTVAR_H

#include "Entities/entity.h"

enum class VarType {
    Unknown = -1,
    Counter,
    Trigger,
    Named
};

class ContextVar : public Entity
{
    ACT_SERIALIZABLE

protected:
    QString name;

    ContextVar();
    ContextVar(const QString& name);
    ContextVar(const QStringList& represent);
    ContextVar(const QByteArray& represent);

public:
    virtual ~ContextVar() = default;

    QString getName() const;
    void setName(const QString& name) noexcept;
};

#endif // CONTEXTVAR_H
