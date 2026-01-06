#ifndef WHILEOPERATOR_H
#define WHILEOPERATOR_H

#include "Entities/Operators/operator.h"
#include "Entities/event.h"


class WhileOperator : public Operator
{
protected:
    Event* body;
    id_type toCompare;

public:
    WhileOperator(id_type variable, Event* body);

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;
};

#endif // WHILEOPERATOR_H
