#ifndef POINTING_H
#define POINTING_H

#include <QSet>
#include <QMap>

class Pointing
{
    static QMap<QString, QString> brackets;

    static QSet<QString> arithmetic;

    static QSet<QString> separators;

public:

    static bool isBracket(const QString& word);

    static bool isLeftBracket(const QString& word);

    static bool isRightBracket(const QString& word);

    static QString leftBracketFor(const QString& right);

    static QString rightBracketFor(const QString& left);

    static bool isValidScopeBounds(const QString& openinig, const QString& closing);

    static bool isArithmetic(const QString& word);

    static bool isSeparator(const QString& word);

    static bool isSingleCommentOpening(const QString& word);
};

#endif // POINTING_H
