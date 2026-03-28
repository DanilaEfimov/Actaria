#include "parser/nodes/statement/definition.h"


/**
 * @brief Definition::Definition
 * @param header
 * @param block
 */
Definition::Definition(const Header &header, const Block &block)
    : Statement(),
    header(header),
    block(block)
{}

/**
 * @brief Definition::getHeader
 * @return
 */
Header Definition::getHeader() const
{
    return header;
}

/**
 * @brief Definition::setHeader
 * @param newHeader
 */
void Definition::setHeader(const Header &newHeader)
{
    this->header = newHeader;
}

/**
 * @brief Definition::getBlock
 * @return
 */
Block Definition::getBlock() const
{
    return this->block;
}

void Definition::setBlock(const Block &newBlock)
{
    block = newBlock;
}
