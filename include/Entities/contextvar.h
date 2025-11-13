/**
 * Interface for context variables: counters, triggers and names
*/

#ifndef CONTEXTVAR_H
#define CONTEXTVAR_H

#include "Entities/entity.h"

class ContextVar : public Entity
{
protected:
    QString name;

    ContextVar();
    ContextVar(const QStringList& represent);
    ContextVar(const QByteArray& represent);

    size_t size() const override;

public:
    virtual ~ContextVar() = default;

    QString getName() const;
    void setName(const QString& name) noexcept;
};

#endif // CONTEXTVAR_H
