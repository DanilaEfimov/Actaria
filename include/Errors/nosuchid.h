#ifndef NOSUCHID_H
#define NOSUCHID_H

#include "error.h"
#include "utils.h"

class NoSuchId : public Error
{
protected:
    using id_type = utils::id_type;

    id_type id;

public:
    NoSuchId(id_type id, QString entityName = "Entity")
        :Error("No " + entityName + " with id: "), id(id)
    {};

    virtual const char* what() const noexcept override {
        QString res = this->message + QString::number(this->id);
        this->cachedWhat = res.toStdString();
        return this->cachedWhat.c_str();
    }

};

#endif // NOSUCHID_H
