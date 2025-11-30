#ifndef EVENT_H
#define EVENT_H

#include "Entities/entity.h"
#include "Entities/operator.h"


class Event : public Entity
{
    using operator_ptr = std::unique_ptr<Operator>;

protected:
    QVector<operator_ptr> onEvent;

    quint32 minimumSize() const override;
    quint32 minimumStrings() const override;

public:
    Event();

    // Entity interface
    hash_type hash() const override;
    size_t size() const override;
    QByteArray serialize() const override;
    void deserialize(const QByteArray &) override;
    QString represent() const override;
    void fromString(const QStringList &) override;

    virtual void exec(Context& context, bool* ok = nullptr) = 0;
};

#endif // EVENT_H
