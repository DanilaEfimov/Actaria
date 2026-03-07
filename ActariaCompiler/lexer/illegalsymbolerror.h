#ifndef ILLEGALSYMBOLERROR_H
#define ILLEGALSYMBOLERROR_H

#include "lexer/lexererror.h"

class IllegalSymbolError : public LexerError
{
public:
    IllegalSymbolError(int col, int line);
};

#endif // ILLEGALSYMBOLERROR_H
