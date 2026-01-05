#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <QString>

class Error : public std::exception
{
protected:
    QString message;
    mutable std::string cachedWhat;

public:
    Error(const char* msg);
    Error(QString&& msg);

    const char* what() const noexcept = 0;
};

#endif // ERROR_H
