#ifndef CYCLE_H
#define CYCLE_H

#include "parser/nodes/statemate.h"
#include "parser/nodes/statement/block.h"
#include "parser/nodes/statement/header.h"

class Cycle : public Statement
{
    Header header;
    Block block;

public:
    Cycle(const Header& header, const Block& block);
    Header getHeader() const;
    void setHeader(const Header &newHeader);
    Block getBlock() const;
    void setBlock(const Block &newBlock);
};

#endif // CYCLE_H
