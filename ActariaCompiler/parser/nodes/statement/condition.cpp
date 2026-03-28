#include "condition.h"


/**
 * @brief Condition::Condition
 * @param header
 * @param blockTrue
 */
Condition::Condition(Header& header, Block& blockTrue)
    : Node(),
    header(header),
    blockTrue(blockTrue),
    blockFalse()
{}

/**
 * @brief Condition::Condition
 * @param header
 * @param blockTrue
 * @param blockFalse
 */
Condition::Condition(Header &header, Block &blockTrue, Block &blockFalse)
    : Node(),
    header(header),
    blockTrue(blockTrue),
    blockFalse(blockFalse)
{}

/**
 * @brief Condition::setFalseBlock
 * @param blockFalse
 */
void Condition::setFalseBlock(const Block& blockFalse)
{
    this->blockFalse = blockFalse;
}

/**
 * @brief Condition::getHeader
 * @return
 */
const Header &Condition::getHeader() const
{
    return this->header;
}

/**
 * @brief Condition::getCondition
 * @return
 */
const Expression &Condition::getCondition() const
{
    return this->header.getParams().at(0);
}

/**
 * @brief Condition::getBlock
 * @return
 */
const Block &Condition::getBlock() const
{
    return this->blockTrue;
}
