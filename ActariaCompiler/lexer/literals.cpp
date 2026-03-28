#include "literals.h"

/**
 * @brief Literals::isNumberLiteral
 * @param word
 * @return
 */
bool Literals::isNumberLiteral(const QString &word)
{
    bool ok = false;

    word.toInt(&ok);

    return ok;
}

/**
 * @brief Literals::isTriggerLiteral
 * @param word
 * @return
 */
bool Literals::isTriggerLiteral(const QString &word)
{
    return word == Literals::falseLiteral
           || word == Literals::trueLiteral;
}

/**
 * @brief Literals::isQuote
 * @param word
 * @return
 */
bool Literals::isQuote(const QString &word)
{
    return word == Literals::textLiteralOpening
           || word == Literals::textLiteralClosing;
}
