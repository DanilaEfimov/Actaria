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
    ContextVar(const QString& name);
    ContextVar(const QStringList& represent);
    ContextVar(const QByteArray& represent);

    size_t size() const override;
    quint32 minimumSize() const override;
    quint32 minimumStrings() const override;

    QByteArray serialize() const override;
    void deserialize(const QByteArray& data) override;
    QString represent() const override;
    void fromString(const QStringList& data) override;

public:
    virtual ~ContextVar() = default;

    QString getName() const;
    void setName(const QString& name) noexcept;

    bool operator<(const ContextVar& other) const noexcept;
};

#endif // CONTEXTVAR_H
