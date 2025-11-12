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

public:
    ContextVar(const QString& name);
    virtual ~ContextVar() = default;

    QString getName() const;
};

#endif // CONTEXTVAR_H
