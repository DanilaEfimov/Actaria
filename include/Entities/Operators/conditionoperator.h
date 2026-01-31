#ifndef CONDITIONOPERATOR_H
#define CONDITIONOPERATOR_H

#include "Entities/Operators/operator.h"
#include "Entities/event.h"
#include "Entities/contextvar.h"


class ConditionOperator : public Operator
{
    ACT_SERIALIZABLE

public:
    using base_t = Operator;
    using ContextValue = ContextVar::ContextValue;

private:
    id_type trueEvent;
    id_type falseEvent;
    bool value;

public:
    ConditionOperator(bool value,
                      id_type trueEvent,
                      id_type falseEvent = UNDEFINED_ID);

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;

    OperatorType type() const override;
};

#endif // CONDITIONOPERATOR_H
