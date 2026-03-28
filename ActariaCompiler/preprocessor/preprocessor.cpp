#include "preprocessor.h"

void Preprocessor::removeEmptyLines(QStringList& source)
{
    for(int i = 0; i < source.size(); i++){
        auto& line = source[i];

        if(line.trimmed().isEmpty()){
            source.removeAt(i);
        }
    }
}

QStringList& Preprocessor::process(QStringList& source)
{
    Preprocessor::removeEmptyLines(source);
    return source;
}
