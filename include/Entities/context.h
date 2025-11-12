#ifndef CONTEXT_H
#define CONTEXT_H

#include "Entities/entity.h"
#include "Entities/contextvar.h"
#include <QSet>

class Context : public Entity
{
    QSet<ContextVar> variables;

public:
    Context();

    // Entity interface
    size_t size() const;
    QByteArray serialize() const;
    void deserialize(const QByteArray& data);
    QString represent() const;
    void fromString(const QString& data);
};

#endif // CONTEXT_H
