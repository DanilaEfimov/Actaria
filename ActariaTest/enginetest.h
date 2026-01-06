#ifndef ENGINETEST_H
#define ENGINETEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "engineinfo.h"

class EngineTest : public QObject
{
    Q_OBJECT

public:
    explicit EngineTest(QObject *parent = nullptr);

private slots:
    void test_serializing();
    void test_id_counting();
    void test_context_algebra();
    void test_OSG();

private:
    static constexpr abi::Version currentVersion = abi::EngineInfo::defaultVersion;

    // Context Variables
    void namedvar_serializing();
    void counter_serializing();
    void trigger_serializing();
    void context_variable_serializing();

    // Context
    void context_serializing();

    // Characters
    void player_serializing();
    void character_serializing();

    // Dialog
    void dialognode_serializing();
    void dialognode_variant_management();
    void dialog_serializing();
};

#endif // ENGINETEST_H
