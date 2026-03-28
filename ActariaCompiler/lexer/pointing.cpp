#include "pointing.h"
#include "illegalsymbolerror.h"


using brackets_t = QPair<QString, QString>;

/**
 * @brief Pointing::brackets
 */
QMap<QString, QString> Pointing::brackets = QMap({
    brackets_t("{", "}"),       // definition scope brackets
    brackets_t("(", ")"),       // arithmetics or operands declaration brackets
    brackets_t("[", "]")        // alias for '[' ']'
});

/**
 * @brief Pointing::arithmetic
 */
QSet<QString> Pointing::arithmetic = QSet<QString>({
    "+",    // integer or text plus
    "-",    // integer minus
    "*",    // integer mull
    "/",    // integer division
    "!",    // trigger denial
    "||",   // trigger 'or'
    "&&",   // trigger 'and'
    "=",    // assignment operator
    "?="    // equals check operator
    ">",    // greater check operator
    "<",    // less check operator
    ">=",   // greater or equals check operator
    "<=",   // less or equals check operator
});

/**
 * @brief Pointing::separators
 */
QSet<QString> Pointing::separators = QSet<QString>({
    ";",    // operators separator
});

/**
 * @brief Pointing::isColon
 * @param word
 * @return
 */
bool Pointing::isColon(const QString &word)
{
    return word.trimmed() == ":";
}

/**
 * @brief Pointing::isIdentifierPart
 * @param ch
 * @return
 */
bool Pointing::isIdentifierPart(QChar ch)
{
    return ch.isLetterOrNumber() || ch == '_';
}

/**
 * @brief Pointing::isIdentifier
 * @param word
 * @return
 */
bool Pointing::isIdentifier(const QString& word)
{
    if (word.isEmpty())
        return false;

    if (!(word[0].isLetter() || word[0] == '_'))
        return false;

    for (int i = 1; i < word.size(); ++i) {
        if (!isIdentifierPart(word[i]))
            return false;
    }

    return true;
}

/**
 * @brief Pointing::isBracket
 * @param word
 * @return
 */
bool Pointing::isBracket(const QString &word)
{
    return Pointing::isLeftBracket(word)
           || Pointing::isRightBracket(word);
}

/**
 * @brief Pointing::isLeftBracket
 * @param word
 * @return
 */
bool Pointing::isLeftBracket(const QString &word)
{
    return Pointing::brackets.keys().contains(word);
}

/**
 * @brief Pointing::isRightBracket
 * @param word
 * @return
 */
bool Pointing::isRightBracket(const QString &word)
{
    return Pointing::brackets.values().contains(word);
}

/**
 * @brief Pointing::leftBracketFor
 * @param right
 * @return
 */
QString Pointing::leftBracketFor(const QString &right)
{
    for(auto it = Pointing::brackets.cbegin(); it != Pointing::brackets.cend(); it++){
        if(it.value() == right)
            return it.key();
    }

    throw IllegalSymbolError("Pointing::leftBracketFor: given string is not a bracket");
}

/**
 * @brief Pointing::rightBracketFor
 * @param left
 * @return
 */
QString Pointing::rightBracketFor(const QString &left)
{
    if(Pointing::brackets.contains(left)){
        return Pointing::brackets[left];
    }

    throw IllegalSymbolError("Pointing::rightBracketFor: given string is not a bracket");
}

/**
 * @brief Pointing::isValidScopeBounds
 * @param openinig
 * @param closing
 * @return
 */
bool Pointing::isValidScopeBounds(const QString &opening, const QString &closing)
{
    if(Pointing::brackets.contains(opening)){
        return Pointing::brackets[opening] == closing;
    }

    return false;
}

/**
 * @brief Pointing::isArithmetic
 * @param word
 * @return
 */
bool Pointing::isArithmetic(const QString &word)
{
    return Pointing::arithmetic.contains(word);
}

/**
 * @brief Pointing::isSeparator
 * @param word
 * @return
 */
bool Pointing::isSeparator(const QString &word)
{
    return Pointing::separators.contains(word);
}

/**
 * @brief Pointing::isSingleCommentOpening
 * @param word
 * @return
 */
bool Pointing::isSingleCommentOpening(const QString &word)
{
    return word.trimmed() == "//";
}
