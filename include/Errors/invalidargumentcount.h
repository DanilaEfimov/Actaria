#ifndef INVALIDARGUMENTCOUNT_H
#define INVALIDARGUMENTCOUNT_H

#include "error.h"

class InvalidArgumentCount : public Error
{
protected:
    int given;
    int required;

public:
    InvalidArgumentCount(const char* msg, int given, int required);
    InvalidArgumentCount(QString msg, int given, int required);

    virtual const char* what() const noexcept override;
};

#endif // INVALIDARGUMENTCOUNT_H
