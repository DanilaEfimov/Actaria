#ifndef OPERATOR_H
#define OPERATOR_H

#include "Entities/entity.h"
#include "Entities/context.h"


/**
 * @brief The operators enum
 */
enum class operators : int {
    assignmentOperator
};

/**
 * @brief The Operator class
 */
class Operator : public Entity {
public:
    /**
     * @brief apply
     * @param context
     */
    virtual void apply(Context& context) const = 0;
    virtual QString toString() const = 0;
    virtual ~Operator() = default;
};

#endif // OPERATOR_H
