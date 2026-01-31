#ifndef JUMPOPERATOR_H
#define JUMPOPERATOR_H

#include "operator.h"


class JumpOperator : public Operator
{
    ACT_SERIALIZABLE

protected:
    id_type node;   // dialog node id

public:
    using base_t = Operator;

    JumpOperator(id_type node);

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;

    OperatorType type() const override;
};

#endif // JUMPOPERATOR_H
