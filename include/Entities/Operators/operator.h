#ifndef OPERATOR_H
#define OPERATOR_H

#include "Entities/entity.h"

class Context;
class Scene;

class Operator : public Entity
{
    ACT_SERIALIZABLE;

public:
    using base_t = Entity;

    Operator();
    Operator(const Operator&) = delete;
    Operator& operator=(const Operator&) = delete;
    virtual ~Operator() = default;

    virtual bool apply(Context& context, Scene& scene) = 0;
};

#endif // OPERATOR_H
