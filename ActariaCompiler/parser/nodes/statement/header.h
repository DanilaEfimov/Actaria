#ifndef HEADER_H
#define HEADER_H

#include "parser/node.h"
#include "parser/nodes/expression.h"
#include "parser/keyword.h"

#include <QVector>

class Header : public Node
{
    using expr = Expression;

    Keyword head;
    QVector<expr> params;

public:
    explicit Header(Keyword head, QVector<expr>&& params);

    QString getHead() const;

    const QVector<expr>& getParams() const;
};

#endif // HEADER_H
