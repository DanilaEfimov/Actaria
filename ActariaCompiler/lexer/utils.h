#ifndef UTILS_H
#define UTILS_H

#include "lexer/token.h"

#include <QString>

class Utils
{
public:
    static QString toString(TokenCategory category);
};

#endif // UTILS_H
