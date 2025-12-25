#ifndef OPERATOR_H
#define OPERATOR_H

#include "Entities/entity.h"
#include "Entities/context.h"


enum class operators : int {
    assignmentOperator
};

class Operator : public Entity {
public:

    virtual QByteArray hexHeader() const override;
    virtual QStringList strHeader() const override;

    virtual void apply(Context& context) const = 0;
    virtual QString toString() const = 0;
    virtual ~Operator() = default;
};

inline QByteArray Operator::hexHeader() const
{

}

inline QStringList Operator::strHeader() const
{

}

#endif // OPERATOR_H
