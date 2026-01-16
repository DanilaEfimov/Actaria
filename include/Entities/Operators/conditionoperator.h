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
    std::shared_ptr<Event> trueEvent;
    std::shared_ptr<Event> falseEvent;
    bool value;

public:
    ConditionOperator(bool value,
                      std::shared_ptr<Event> trueEvent,
                      std::shared_ptr<Event> falseEvent = nullptr);

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;

    OperatorType type() const override;
};

#endif // CONDITIONOPERATOR_H
