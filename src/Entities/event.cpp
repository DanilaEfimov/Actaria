#include "Entities/event.h"


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
    return this->operators.count();
}
