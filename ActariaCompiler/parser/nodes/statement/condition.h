#ifndef CONDITION_H
#define CONDITION_H

#include "parser/node.h"
#include "parser/nodes/statement/header.h"
#include "parser/nodes/statement/block.h"

class Condition : public Node
{
    Header header;
    Block blockTrue;
    Block blockFalse;

public:
    explicit Condition(Header& header, Block& blockTrue);
    explicit Condition(Header& header, Block& blockTrue, Block& blockFalse);

    void setFalseBlock(const Block& blockFalse);

    const Header& getHeader() const;

    const Expression& getCondition() const;

    const Block& getBlock() const;
};

#endif // CONDITION_H
