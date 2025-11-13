#include "GUI/mainwindow.h"
#include "Entities/contextcounter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();

    ContextCounter c("mana", 75);
    QByteArray data = c.serialize();
    qDebug() << "Serialized size:" << data.size();
    qDebug() << "Expected size:" << c.size();

    ContextCounter d("", 0);
    d.deserialize(data);

    qDebug() << "Original:" << c.represent();
    qDebug() << "Deserialized:" << d.represent();
    qDebug() << "Binary serialization test passed?" << (c.represent() == d.represent());

    ContextCounter b = ContextCounter::parse("10086086306237813280::23::4321::points");
    qDebug() << b.represent();

    return 0;
}
