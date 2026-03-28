#include "keyword.h"
#include "lexer/keywords.h"
#include "parser/unexceptedsymbol.h"

/**
 * @brief Keyword::Keyword
 * @param word
 */
Keyword::Keyword(const Token &token)
    : word(token.getValue())
{
    if(!KeyWords::contains(token.getValue()))
        throw UnexceptedSymbol(TokenCategory::Keyword, token.getCategory());
}

/**
 * @brief Keyword::get
 * @return
 */
const QString &Keyword::get() const
{
    return this->word;
}
