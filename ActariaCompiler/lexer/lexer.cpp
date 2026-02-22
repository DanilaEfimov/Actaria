#include "lexer.h"
#include "token.h"

Lexer::Lexer(const text_t& source)
    : source(source)
{}

Token Lexer::nextToken() const
{

}

Token Lexer::peekToken(int n) const
{

}

bool Lexer::isEof() const
{
    return this->peekToken().getCategory() == TokenCategory::Eof;
}

Position Lexer::getPosition() const
{
    return this->pos;
}
