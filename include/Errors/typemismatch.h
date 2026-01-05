#ifndef TYPEMISMATCH_H
#define TYPEMISMATCH_H

#include "error.h"

enum class VarType;

class TypeMismatch : public Error
{
protected:
    VarType type1;
    VarType type2;

public:
    TypeMismatch(const char* msg, VarType t1, VarType t2);
    TypeMismatch(QString&& msg, VarType t1, VarType t2);

    virtual const char* what() const noexcept override;
};

#endif // TYPEMISMATCH_H
