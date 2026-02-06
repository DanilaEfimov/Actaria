#include "Errors/invalidsignature.h"
#include "utils.h"


/**
 * @brief InvalidSignature::InvalidSignature
 * @param msg
 * @param sign
 */
InvalidSignature::InvalidSignature(const char *msg, Signature &&sign, ContextAlgebra op)
    : Error(msg), given(std::move(sign)), op(op)
{}

/**
 * @brief InvalidSignature::InvalidSignature
 * @param msg
 * @param sign
 */
InvalidSignature::InvalidSignature(QString &&msg, Signature &&sign, ContextAlgebra op)
    : Error(std::move(msg)), given(sign), op(op)
{}

/**
 * @brief InvalidSignature::what
 * @return formated error message
 */
const char* InvalidSignature::what() const noexcept
{
    QString res = "Unexpected signature for operation: " + QString::number(static_cast<int>(this->op));
    QString sign = [this]() -> QString {
        QString s = "";
        auto it = this->given.begin();
        for(size_t i = 0; i < this->given.size(); i++){
            s += utils::contextValueTypeString(*(it + i));
            if(i + 1 < this->given.size())
                s += ", ";
        }
    }();
    res += " : given [" + sign + "] : ";
    res += this->message;
    this->cachedWhat = res.toStdString();
    return this->cachedWhat.c_str();
}
