#include "Errors/typemismatch.h"
#include "utils.h"


/**
 * @brief TypeMismatch::TypeMismatch
 * @param msg
 * @param t1
 * @param t2
 */
TypeMismatch::TypeMismatch(const char *msg, VarType t1, VarType t2)
    : Error(msg), type1(t1), type2(t2)
{}

/**
 * @brief TypeMismatch::TypeMismatch
 * @param msg
 * @param t1
 * @param t2
 */
TypeMismatch::TypeMismatch(QString&& msg, VarType t1, VarType t2)
    : Error(std::move(msg)), type1(t1), type2(t2)
{}

/**
 * @brief TypeMismatch::what
 * @return formated error message
 */
const char* TypeMismatch::what() const noexcept
{
    QString res = "Type mismatch: ";
    QString t1 = utils::ContextValueTypeString(type1);
    QString t2 = utils::ContextValueTypeString(type2);

    res += t1 + " and " + t2 + " : " + this->message;

    this->cachedWhat = res.toStdString();
    return this->cachedWhat.c_str();
}
