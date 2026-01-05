#ifndef NOSUCHVARIABLE_H
#define NOSUCHVARIABLE_H

#include "error.h"
#include "utils.h"

class NoSuchVariable : public Error {

    utils::id_type id;

public:

    NoSuchVariable(utils::id_type id)
        : Error("No variable with such id: "), id(id)
    {};

    virtual const char* what() const noexcept override {
        QString res = this->message + QString::number(this->id);
        this->cachedWhat = res.toStdString();
        return this->cachedWhat.c_str();
    }

};

#endif // NOSUCHVARIABLE_H
