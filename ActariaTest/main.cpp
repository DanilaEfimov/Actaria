#include <QCoreApplication>
#include "enginetest.h"

#define ACTARIA_TEST

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int verdict = 0;

    EngineTest engineTest;
    verdict |= QTest::qExec(&engineTest, argc, argv);

    return verdict;
}
