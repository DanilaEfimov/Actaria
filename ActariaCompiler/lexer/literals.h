#ifndef LITERALS_H
#define LITERALS_H

#include <QString>

class Literals
{
    static constexpr const char* textLiteralOpening = "\"";
    static constexpr const char* textLiteralClosing = textLiteralOpening;

    static constexpr const char* trueLiteral = "true";
    static constexpr const char* falseLiteral = "false";

public:
    static bool isNumberLiteral(const QString& word);

    static bool isTriggerLiteral(const QString& word);

    static bool isQuote(const QString& word);
};

#endif // LITERALS_H
