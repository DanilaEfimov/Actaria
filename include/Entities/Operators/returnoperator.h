#ifndef RETURNOPERATOR_H
#define RETURNOPERATOR_H

#include "operator.h"

class Event;

class ReturnOperator : public Operator
{
    ACT_SERIALIZABLE

public:
    using base_t = Operator;

    static constexpr int magic_mark = static_cast<int>(utils::fnv1a_64("returnoperator"));

    ReturnOperator();

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;

    OperatorType type() const override;
};

#endif // RETURNOPERATOR_H
