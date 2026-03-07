#include "lexer.h"
#include "keywords.h"
#include "pointing.h"
#include "literals.h"


/**
 * @brief Lexer::checkCategory
 * @param value
 * @return
 */
void Lexer::increment() noexcept
{
    if(this->isEof()) return;

    auto currentLine = this->source.at(this->pos.line);

    if(this->pos.column + 1 < currentLine.size())
        this->pos.column++;
    else{
        this->pos.line++;
        this->pos.column = 0;
    }
}

/**
 * @brief Lexer::checkCategory
 * @param value
 * @return
 */
TokenCategory Lexer::checkCategory(const QString &value)
{
    // keywords checking
    if(KeyWords::contains(value)) return TokenCategory::Keyword;

    // pointing checking
    else if(Pointing::isArithmetic(value)) return TokenCategory::Arithmetic;
    else if(Pointing::isLeftBracket(value)) return TokenCategory::LBrace;
    else if(Pointing::isRightBracket(value)) return TokenCategory::RBrace;
    else if(Pointing::isSeparator(value)) return TokenCategory::Separator;
    else if(Pointing::isSingleCommentOpening(value)) return TokenCategory::SingleComment;

    // literal checking
    else if(Literals::isNumberLiteral(value)) return TokenCategory::TextLiteral;
    else if(Literals::isTextLiteral(value)) return TokenCategory::TextLiteral;
    else if(Literals::isTriggerLiteral(value)) return TokenCategory::TriggerLiteral;

    // default
    else return TokenCategory::Identifier;
}

/**
 * @brief Lexer::Lexer
 * @param source
 */
Lexer::Lexer(const text_t& source)
    : source()
{
    for(auto& line : source) {
        text_t tokens = line.split("\\s+");
        this->source.append(tokens);
    }
}

/**
 * @brief Lexer::nextToken
 * @return
 */
Token Lexer::nextToken()
{
    QString value = this->source
                        .at(this->pos.line)
                        .at(this->pos.column);

    TokenCategory category = Lexer::checkCategory(value);

    this->increment();

    return Token(category, value);
}

/**
 * @brief Lexer::peekToken
 * @param n
 * @return
 */
Token Lexer::peekToken(int n) const
{
    if(this->isEof()) return Token(TokenCategory::Eof);

    const text_t& currentLine = this->source.at(this->pos.line);

    QString value = currentLine.at(this->pos.column + n);
    TokenCategory category = this->checkCategory(value);

    return Token(category, value);
}

/**
 * @brief Lexer::isEof
 * @return
 */
bool Lexer::isEof() const
{
    const text_t& currentLine = this->source[this->pos.line];

    if((this->pos.line == this->source.size() - 1)
        && this->pos.column >= currentLine.size())
        return true;

    return false;
}

/**
 * @brief Lexer::getPosition
 * @return
 */
Position Lexer::getPosition() const
{
    return this->pos;
}
