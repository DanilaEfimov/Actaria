#include "unexceptedsymbol.h"
#include "lexer/utils.h"


/**
 * @brief UnexceptedSymbol::UnexceptedSymbol
 * @param category
 * @param msg
 */
UnexceptedSymbol::UnexceptedSymbol(TokenCategory excepted, TokenCategory given)
    : ParserError(
          QString("Unexpected token: expected %1 but got %2")
              .arg(Utils::toString(excepted))
              .arg(Utils::toString(given))
          .toStdString()
          .c_str()
    )
    ,excepted(excepted),
    given(given)
{}
