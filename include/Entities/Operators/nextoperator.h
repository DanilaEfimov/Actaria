#ifndef NEXTOPERATOR_H
#define NEXTOPERATOR_H

#include "Entities/Operators/operator.h"
#include "Entities/scene.h"

class NextOperator : public Operator
{
protected:
    Scene* next;

public:
    NextOperator(Scene* newScene);

    hash_type hash() const override;

    bool apply(Context &context, Scene &scene) override;
};

#endif // NEXTOPERATOR_H
