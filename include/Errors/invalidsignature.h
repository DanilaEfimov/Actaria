#ifndef INVALIDSIGNATURE_H
#define INVALIDSIGNATURE_H

#include "error.h"

enum class VarType;
enum class ContextAlgebra;

class InvalidSignature : public Error
{
    using Signature = std::initializer_list<VarType>;

    Signature given;
    ContextAlgebra op;

public:
    InvalidSignature(const char* msg, Signature&& sign, ContextAlgebra op);
    InvalidSignature(QString&& msg, Signature&& sign, ContextAlgebra op);

    virtual const char* what() const noexcept override;
};

#endif // INVALIDSIGNATURE_H
