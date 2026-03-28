#ifndef UNEXCEPTEDSYMBOL_H
#define UNEXCEPTEDSYMBOL_H

#include "parser/parsererror.h"
#include "lexer/token.h"

class UnexceptedSymbol : public ParserError
{
    TokenCategory excepted;
    TokenCategory given;

public:
    explicit UnexceptedSymbol(TokenCategory excepted, TokenCategory given);
};

#endif // UNEXCEPTEDSYMBOL_H
