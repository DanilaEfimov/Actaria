#ifndef OPERATOR_H
#define OPERATOR_H

#include "Entities/entity.h"

class Context;
class Scene;

enum class OperatorType {
    Assignment,
    While,
    Condition,
    Jump,
    Next,
    Call,
    Return
};

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

    virtual OperatorType type() const = 0;
};

/**
 * @warning The dynamic type of `o` MUST match the serialized OperatorType.
 * Undefined behavior otherwise.
 */

namespace fix {

void write(QDataStream& out, const Operator& o);
void write(StringListCursor& out, const Operator& o);

void read(QDataStream& in, Operator& o);
void read(StringListCursor& in, Operator& o);

}

#endif // OPERATOR_H
