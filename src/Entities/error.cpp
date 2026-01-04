#include "error.h"


/**
 * @brief Error::Error
 * @param msg
 */
Error::Error(const char* msg)
    : std::exception(), message(msg)
{}

/**
 * @brief Error::Error
 * @param msg
 */
Error::Error(QString &&msg)
    : std::exception(), message(msg)
{}
