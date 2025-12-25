#ifndef EVENT_H
#define EVENT_H

#include "Entities/entity.h"
#include "Entities/operator.h"


class Event : public Entity
{
    using operator_ptr = QScopedPointer<Operator>;

protected:
    QVector<operator_ptr> operators;

public:
    Event();

    virtual QByteArray hexHeader() const override;
    virtual QStringList strHeader() const override;

    virtual bool exec(Context* context) const = 0;
};

#endif // EVENT_H
