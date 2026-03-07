#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <QSet>

class KeyWords
{
    static QSet<QString> typeNames;
    static QSet<QString> keywords;

public:

    static bool contains(const QString& word);

    static bool isTypeName(const QString& word);
};

#endif // KEYWORDS_H
