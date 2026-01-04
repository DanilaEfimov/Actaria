#include "Entities/event.h"
#include "Entities/Operators/operator.h"


/**
 * @brief Event::Event
 */
Event::Event()
    : Entity(), operators()
{}

/**
 * @brief Event::clear
 */
void Event::clear() noexcept
{
    this->operators.clear();
}

/**
 * @brief Event::operatorCount
 * @return actual count of operators
 */
qsizetype Event::operatorCount() const
{
    return this->operators.size();
}

/**
 * @brief Event::addOpertor
 * @param op
 */
void Event::addOpertor(operator_p &&op)
{
    this->operators.push_back(std::move(op));
}

/**
 * @brief Event::removeOperator
 * @param idx
 */
void Event::removeOperator(qsizetype idx)
{
    auto it = this->operators.cbegin();
    this->operators.erase(it + idx);
}
