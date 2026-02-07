#include "datastreamcursor.h"

#include "QDataStream"


/// operator >>

/**
 * @brief operator <<
 * @param out
 * @param value
 * @return
 */
DataStreamCursor& operator<<(DataStreamCursor& out, const ContextValue& value) {
    utils::writeValue(out, value);
    return out;
}

/// operator <<

/**
 * @brief operator >>
 * @param in
 * @param value
 * @return
 */
DataStreamCursor& operator>>(DataStreamCursor& in, ContextValue& value) {
    utils::readValue(in, value);
    return in;
}

/**
 * @brief DataStreamCursor::DataStreamCursor
 */
DataStreamCursor::DataStreamCursor()
    : stream()
{
    this->stream.setByteOrder(EngineInfo::endian);
}

/**
 * @brief DataStreamCursor::DataStreamCursor
 * @param arr
 */
DataStreamCursor::DataStreamCursor(const QByteArray &arr)
    : stream(arr)
{}

/**
 * @brief DataStreamCursor::DataStreamCursor
 * @param device
 * @param m
 */
DataStreamCursor::DataStreamCursor(QByteArray* device, QIODeviceBase::OpenModeFlag m)
    : stream(device, m)
{
    this->stream.setByteOrder(EngineInfo::endian);
}

/**
 * @brief DataStreamCursor::DataStreamCursor
 * @param device
 */
DataStreamCursor::DataStreamCursor(QIODevice& device)
    : stream(&device)
{
    this->stream.setByteOrder(EngineInfo::endian);
}

/**
 * @brief DataStreamCursor::startTransaction
 */
void DataStreamCursor::startTransaction()
{
    this->stream.startTransaction();
}

/**
 * @brief DataStreamCursor::rollbackTransaction
 */
void DataStreamCursor::rollbackTransaction()
{
    this->stream.rollbackTransaction();
}

/**
 * @brief DataStreamCursor::commitTransaction
 */
void DataStreamCursor::commitTransaction()
{
    this->stream.commitTransaction();
}

/**
 * @brief DataStreamCursor::skipRawData
 * @param len
 * @return
 */
qint64 DataStreamCursor::skipRawData(int len)
{
    return this->stream.skipRawData(len);
}

/**
 * @brief DataStreamCursor::data
 * @return
 */
QDataStream &DataStreamCursor::data()
{
    return this->stream;
}

/**
 * @brief DataStreamCursor::data
 * @return
 */
const QDataStream &DataStreamCursor::data() const
{
    return this->stream;
}
