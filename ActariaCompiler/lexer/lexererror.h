#ifndef LEXERERROR_H
#define LEXERERROR_H

#include <stdexcept>
#include <QString>

class LexerError : public std::runtime_error {
public:
    LexerError(const QString& msg, int line = -1, int col = -1)
        : std::runtime_error(msg.toStdString()), line(line), column(col) {}

    int line;
    int column;
};

#endif // LEXERERROR_H
