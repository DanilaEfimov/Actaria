#ifndef JUMPOPERATOR_H
#define JUMPOPERATOR_H

#include "operator.h"

class JumpOperator : public Operator
{
protected:
    id_type mark;   // dialog node id

public:
    JumpOperator(id_type node);

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;
};

#endif // JUMPOPERATOR_H
