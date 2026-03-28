#include "block.h"


/**
 * @brief Block::Block
 * @param childs
 */
Block::Block(QVector<node>& childs)
    : childs(std::move(childs))
{}

/**
 * @brief Block::count
 * @return
 */
int Block::count() const
{
    return this->childs.count();
}

/**
 * @brief Block::get
 * @param n
 * @return
 */
const Node& Block::get(int n) const
{
    return this->childs.at(n);
}

/**
 * @brief Block::apend
 * @param child
 */
void Block::apend(node child)
{
    this->childs.append(std::move(child));
}

/**
 * @brief Block::pop
 * @param n
 */
void Block::pop(int n)
{
    this->childs.remove(n);
}
