#include "Errors/invalidargumentcount.h"


/**
 * @brief InvalidArgumentCount::InvalidArgumentCount
 * @param msg
 * @param given
 * @param required
 */
InvalidArgumentCount::InvalidArgumentCount(const char *msg, int given, int required)
    : Error(msg), given(given), required(required)
{}

/**
 * @brief InvalidArgumentCount::InvalidArgumentCount
 * @param msg
 * @param given
 * @param required
 */
InvalidArgumentCount::InvalidArgumentCount(QString msg, int given, int required)
    : Error(std::move(msg)), given(given), required(required)
{}

/**
 * @brief InvalidArgumentCount::what
 * @return
 */
const char* InvalidArgumentCount::what() const noexcept
{
    QString res = "Invalid argument count : ";
    res += "given " + QString::number(this->given)
           +  "required " + QString::number(this->required)
           + " : " + this->message;

    this->cachedWhat = res.toStdString();
    return this->cachedWhat.c_str();
}
