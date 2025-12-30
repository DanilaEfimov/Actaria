#include "stringlistcursor.h"
#include "Entities/counter.h"
#include "engineinfo.h"
#include "readwrite.h"

#include <QApplication>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StringListCursor cursor;
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);

    Counter counter(23, "retries");

    // Запись в StringListCursor
    abi::write<decltype(counter), EngineInfo::defaultVersion>(cursor, counter);

    qDebug() << "--- StringListCursor output ---";
    qDebug() << cursor.list().join(EngineInfo::separator);

    // Запись в QDataStream
    abi::write<decltype(counter), EngineInfo::defaultVersion>(out, counter);

    qDebug() << "--- QDataStream output (hex) ---";
    qDebug() << buffer.toHex(' ');
    qDebug() << "--- QDataStream output (as utf-8, for debugging) ---";
    qDebug() << QString::fromUtf8(buffer);

    return a.exec();
}
