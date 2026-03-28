#ifndef BLOCK_H
#define BLOCK_H

#include "parser/node.h"

#include <QVector>

class Block : public Node
{
    using node = Node;

    QVector<node> childs;

public:
    Block() = default;

    explicit Block(QVector<node>& childs);

    int count() const;

    const Node& get(int n) const;

    void apend(node child);

    void pop(int n = 0);
};

#endif // BLOCK_H
