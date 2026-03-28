#ifndef DEFINITION_H
#define DEFINITION_H

#include "parser/nodes/statemate.h"
#include "parser/nodes/statement/header.h"
#include "parser/nodes/statement/block.h"

class Definition : public Statement
{
    Header header;
    Block block;

public:
    Definition(const Header& header, const Block& block);

    Header getHeader() const;
    void setHeader(const Header &newHeader);
    Block getBlock() const;
    void setBlock(const Block &newBlock);
};

#endif // DEFINITION_H
