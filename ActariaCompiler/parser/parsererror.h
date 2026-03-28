#ifndef PARSERERROR_H
#define PARSERERROR_H

#include <stdexcept>

class ParserError : public std::runtime_error
{
public:
    ParserError(const char* msg);
};

#endif // PARSERERROR_H
