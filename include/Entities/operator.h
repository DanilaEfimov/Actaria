#ifndef OPERATOR_H
#define OPERATOR_H

#include "Entities/entity.h"
#include "Entities/context.h"


enum class operators : int {
    assignmentOperator
};

class Operator : public Entity {
public:
    virtual void apply(Context& context) const = 0;
    virtual QString toString() const = 0;
    virtual ~Operator() = default;
};

#endif // OPERATOR_H
