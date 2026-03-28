#include "parsererror.h"

ParserError::ParserError(const char* msg)
    : std::runtime_error(msg)
{}
