/**
 *  @file datastreamcursor.h
 *  here defined overload-based wrapper for QDataStream.
 */

#ifndef DATASTREAMCURSOR_H
#define DATASTREAMCURSOR_H

#include "common.h"
#include "utils.h"
#include "readwrite.h"

#include <QDataStream>
#include <QBuffer>
#include <QFile>


class DataStreamCursor {
    QDataStream stream;

public:
    DataStreamCursor();
    DataStreamCursor(const QByteArray& arr);
    explicit DataStreamCursor(QIODevice& device);
    ~DataStreamCursor() = default;

    void startTransaction();
    void rollbackTransaction();
    void commitTransaction();

    qint64 skipRawData(int len);

    QDataStream& data();
    const QDataStream& data() const;
};

/// operator <<
template<typename T>
DataStreamCursor& operator<<(DataStreamCursor& out, const T& value) {
    out.data() << value;
    return out;
}

template<utils::NotGameEntity T>
DataStreamCursor& operator<<(DataStreamCursor& out, const T& value) {
    out.data() << value;
    return out;
};

template<utils::GameEntity T>
DataStreamCursor& operator<<(DataStreamCursor& out, const T& value) {
    abi::write<T, EngineInfo::defaultVersion>(out.data(), value);
    return out;
};

DataStreamCursor& operator<<(DataStreamCursor& out, const ContextValue& value);;

/// operator >>
template<typename T>
DataStreamCursor& operator>>(DataStreamCursor& in, const T& value) {
    in.data() >> value;
    return in;
}

template<utils::NotGameEntity T>
DataStreamCursor& operator>>(DataStreamCursor& in, T& value) {
    in.data() >> value;
    return in;
};

template<utils::GameEntity T>
DataStreamCursor& operator>>(DataStreamCursor& in, T& value) {
    abi::read<T, EngineInfo::defaultVersion>(in.data(), value);
    return in;
};

DataStreamCursor& operator>>(DataStreamCursor& in, ContextValue& value);

#endif // DATASTREAMCURSOR_H
