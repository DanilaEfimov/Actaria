#include "lexer.h"
#include "keywords.h"
#include "pointing.h"
#include "literals.h"

Lexer::Lexer(const QStringList& sourceLines)
    : source(sourceLines), pos{0, 0}
{}

void Lexer::increment() noexcept
{
    this->pos.column++;
    if (this->pos.column >= this->currentWords.size()) {
        this->pos.line++;
        this->pos.column = 0;
        this->currentWords.clear();
    }
}

TokenCategory Lexer::checkCategory(const QString& value)
{
    if (KeyWords::contains(value)) return TokenCategory::Keyword;
    // keywords ^^^ / pointing vvv
    if (Pointing::isArithmetic(value)) return TokenCategory::Arithmetic;
    if (Pointing::isLeftBracket(value)) return TokenCategory::LBrace;
    if (Pointing::isRightBracket(value)) return TokenCategory::RBrace;
    if (Pointing::isSeparator(value)) return TokenCategory::Separator;
    if (Pointing::isSingleCommentOpening(value)) return TokenCategory::SingleComment;
    if (Pointing::isColon(value)) return TokenCategory::Colon;
    // pointing ^^^ / literals vvv
    if (Literals::isNumberLiteral(value)) return TokenCategory::NumberLiteral;
    if (Literals::isQuote(value)) return TokenCategory::Quote;
    if (Literals::isTriggerLiteral(value)) return TokenCategory::TriggerLiteral;
    // default vvv
    if (Pointing::isIdentifier(value)) return TokenCategory::Identifier;
    return TokenCategory::Unknown;
}

Token Lexer::collectTextLiteral()
{
    QString value;
    this->increment();

    while (true) {
        if (this->pos.column >= this->currentWords.size()) {
            if (this->isEof()) break;
            this->tokenizeCurrentLine();
            this->pos.column = 0;
            if (this->currentWords.isEmpty()) break;
        }

        QString part = this->currentWords[this->pos.column];
        TokenCategory partCat = this->checkCategory(part);
        this->increment();

        if (partCat == TokenCategory::Quote) {
            break;
        }

        if (!value.isEmpty()) value.append(' ');
        value.append(part);
    }

    return Token(TokenCategory::TextLiteral, value);
}

bool Lexer::isEof() const
{
    return pos.line >= source.size();
}

Position Lexer::getPosition() const
{
    return pos;
}

void Lexer::tokenizeCurrentLine()
{
    this->currentWords.clear();
    if (this->isEof()) return;

    const QString& line = this->source[pos.line];
    QString token;

    for (QChar ch : line) {
        if (Pointing::isIdentifierPart(ch)) {
            token += ch;
        } else {
            if (!token.isEmpty()) {
                this->currentWords.append(token);
                token.clear();
            }

            if (!ch.isSpace()) {
                this->currentWords.append(QString(ch));
            }
        }
    }

    if (!token.isEmpty()) {
        this->currentWords.append(token);
    }

    this->pos.column = 0;
}

Token Lexer::nextToken()
{
    if (this->isEof())
        return Token(TokenCategory::Eof);

    while (this->currentWords.isEmpty() || this->pos.column >= this->currentWords.size()) {
        this->tokenizeCurrentLine();
        if (this->currentWords.isEmpty()) {
            this->pos.line++;
            if (this->isEof())
                return Token(TokenCategory::Eof);
            continue;
        }
        this->pos.column = 0;
    }

    QString value = this->currentWords[pos.column];
    TokenCategory cat = this->checkCategory(value);

    if (cat == TokenCategory::Quote) {
        return this->collectTextLiteral();
    }

    this->increment();
    if (this->pos.column >= this->currentWords.size()) {
        this->currentWords.clear();
    }

    return Token(cat, value);
}

Token Lexer::peekToken(int n) const
{
    if (this->isEof())
        return Token(TokenCategory::Eof);

    QStringList words = this->source[pos.line].split(' ', Qt::SkipEmptyParts);
    int peekPos = this->pos.column + n;
    if (peekPos >= words.size())
        return Token(TokenCategory::Eof);

    return Token(this->checkCategory(words[peekPos]), words[peekPos]);
}
