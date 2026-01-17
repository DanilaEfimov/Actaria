#ifndef WHILEOPERATOR_H
#define WHILEOPERATOR_H

#include "Entities/Operators/operator.h"
#include "Entities/event.h"


class WhileOperator : public Operator
{
    ACT_SERIALIZABLE

protected:
    id_type body;       // id of cycle body event
    id_type toCompare;  // id of condition variable

public:
    using base_t = Operator;

    WhileOperator(id_type variable, id_type body);

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;

    OperatorType type() const override;
};

#endif // WHILEOPERATOR_H
