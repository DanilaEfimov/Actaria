#ifndef IMPORT_H
#define IMPORT_H

#include "parser/node.h"
#include "parser/nodes/expressions/identifier.h"

class Import : public Node
{
    Identifier symbol;

public:
    explicit Import(const Identifier& symbol);

    const QString& getName() const;
};

#endif // IMPORT_H
