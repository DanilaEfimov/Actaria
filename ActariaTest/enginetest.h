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
    void test_processing();
    void test_utils_processing();
    void test_id_counting();
    void test_context_algebra();
    void test_OSG();

private:
    static constexpr abi::Version currentVersion = abi::EngineInfo::defaultVersion;

    /* Context Variables */
    // serializing vvv
    void namedvar_serializing();
    void counter_serializing();
    void trigger_serializing();
    void context_variable_serializing();
    // ^^^ serializing / processing vvv
    void context_variables_processing();

    // Context
    void context_serializing();

    // Characters
    void player_serializing();
    void character_serializing();

    /* Operators */
    // serializing vvv
    void operators_serializing();
    void jump_operator_serializing();
    void call_operator_serializing();
    void next_operator_serializing();
    void return_operator_serializing();
    void while_operator_serializing();
    void condition_operator_serializing();
    void assignment_operator_serializing();
    // ^^^ serializing / processing vvv
    void operators_processing();
    void jump_operator_processing();
    void call_operator_processing();
    void next_operator_processing();
    void return_operator_processing();
    void while_operator_processing();
    void condition_operator_processing();
    void assignment_operator_processing();

    // Dialog
    void dialognode_serializing();
    void dialognode_variant_management();
    void dialog_serializing();

    // Scene
    void scene_serializing();
};

#endif // ENGINETEST_H
