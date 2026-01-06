#ifndef CONDITIONOPERATOR_H
#define CONDITIONOPERATOR_H

#include "Entities/Operators/operator.h"
#include "Entities/event.h"
#include "Entities/contextvar.h"


class ConditionOperator : public Operator
{
    ACT_SERIALIZABLE

    using ContextValue = ContextVar::ContextValue;

    std::unique_ptr<Event> trueEvent;
    std::unique_ptr<Event> falseEvent;
    bool value;

public:
    ConditionOperator(bool value,
                      std::unique_ptr<Event> trueEvent,
                      std::unique_ptr<Event> falseEvent = nullptr);

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;
};

#endif // CONDITIONOPERATOR_H
