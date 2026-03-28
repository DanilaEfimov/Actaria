#include "cycle.h"


/**
 * @brief Cycle::getHeader
 * @return
 */
Header Cycle::getHeader() const
{
    return this->header;
}

/**
 * @brief Cycle::setHeader
 * @param newHeader
 */
void Cycle::setHeader(const Header &newHeader)
{
    this->header = newHeader;
}

/**
 * @brief Cycle::getBlock
 * @return
 */
Block Cycle::getBlock() const
{
    return this->block;
}

/**
 * @brief Cycle::setBlock
 * @param newBlock
 */
void Cycle::setBlock(const Block &newBlock)
{
    this->block = newBlock;
}

/**
 * @brief Cycle::Cycle
 * @param header
 * @param block
 */
Cycle::Cycle(const Header &header, const Block &block)
    : Statement(),
    header(header),
    block(block)
{}
