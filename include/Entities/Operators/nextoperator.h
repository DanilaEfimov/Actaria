#ifndef NEXTOPERATOR_H
#define NEXTOPERATOR_H

#include "Entities/Operators/operator.h"
#include "Entities/scene.h"

class NextOperator : public Operator
{
    ACT_SERIALIZABLE

protected:
    id_type next;       // id of next scene

public:
    using base_t = Operator;

    NextOperator(id_type newScene);

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;

    OperatorType type() const override;
};

#endif // NEXTOPERATOR_H
