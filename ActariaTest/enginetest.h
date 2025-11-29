#ifndef ENGINETEST_H
#define ENGINETEST_H

#include <QObject>
#include <QtTest/QtTest>

class EngineTest : public QObject
{
    Q_OBJECT

public:
    explicit EngineTest(QObject *parent = nullptr);

private slots:
    void test_serializing();
    void test_id_counting();
    void test_OSG();    // oriented story graph
};

#endif // ENGINETEST_H
