#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <QStringList>

class Preprocessor
{
    static void removeEmptyLines(QStringList& source);

public:

    static QStringList& process(QStringList& source);
};

#endif // PREPROCESSOR_H
