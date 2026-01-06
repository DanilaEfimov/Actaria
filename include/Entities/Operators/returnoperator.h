#ifndef RETURNOPERATOR_H
#define RETURNOPERATOR_H

#include "operator.h"

class Event;

class ReturnOperator : public Operator
{
    ACT_SERIALIZABLE

    Event* caller;

public:
    ReturnOperator(Event* caller);

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;
};

#endif // RETURNOPERATOR_H
