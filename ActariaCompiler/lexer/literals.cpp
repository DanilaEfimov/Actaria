#include "literals.h"


/**
 * @brief Literals::isTextLiteral
 * @param word
 * @return
 */
bool Literals::isTextLiteral(const QString &word)
{
    return word.startsWith(Literals::textLiteralOpening)
           && word.endsWith(Literals::textLiteralClosing);
}

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
