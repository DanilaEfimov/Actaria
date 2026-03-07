#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "parser/nodes/expression.h"

#include <QString>

class Identifier : public Expression
{
    QString name;

public:
    explicit Identifier(const QString& name);

    const QString& getName() const;
};

#endif // IDENTIFIER_H
