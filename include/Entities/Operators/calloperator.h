#ifndef CALLOPERATOR_H
#define CALLOPERATOR_H

#include "Entities/Operators/operator.h"

class CallOperator : public Operator
{
    ACT_SERIALIZABLE

    id_type event;

public:
    CallOperator(id_type eventId);

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;

    OperatorType type() const override;
};

#endif // CALLOPERATOR_H
