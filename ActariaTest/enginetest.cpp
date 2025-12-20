#include "enginetest.h"
#include "testutils.h"
#include "namevar.h"
#include "counter.h"
#include "trigger.h"
#include "contextvarfabric.h"
#include "player.h"
#include "dialognode.h"

namespace {
    // Context Variables tests vvv
void namedvar_serializing(){
    QStringList names = {
        "Danila", "", "-1201-20*@&#&!@%#!&", "Данила",
        "Lg&Fw3[09F0p#*fyO8&fuhp#(F-0_3F9_(*#f#f_#8F_f"
    };
    for(int i = 0; i < 20; i++){
        int size_inc = (i*i+7*i+10)%100;
        names.append(randomString(10 + size_inc));
    }

    for(const auto& name : names){
        NameVar variable(name, randomString(10));
        QByteArray data = variable.serialize();
        QString represent = variable.represent();
        auto varptr = ContextVarFabric::make<NameVar>(data);
        QCOMPARE(varptr->serialize(), data);
        QCOMPARE(varptr->represent(), represent);
    }
};

void counter_serializing(){
    QList<int> values = {
        0, 1, -1, INT_MAX, INT_MIN
    };
    for(int i = 0; i < 20; i++){
        values.append(i*i*i*i+0xFFFF);
    }

    for(const auto& value : values){
        Counter variable(value, randomString(10));
        QByteArray data = variable.serialize();
        QString represent = variable.represent();
        auto varptr = ContextVarFabric::make<Counter>(data);
        QCOMPARE(varptr->serialize(), data);
        QCOMPARE(varptr->represent(), represent);
    }
};

void trigger_serializing(){
    Trigger triggerT(true, "game_trigger");
    Trigger triggerF(false, "game_trigger");

    {
        QByteArray data = triggerT.serialize();
        QString represent = triggerT.represent();
        auto varptr = ContextVarFabric::make<Trigger>(data);
        QCOMPARE(varptr->serialize(), data);
        QCOMPARE(varptr->represent(), represent);
    }
    {
        QByteArray data = triggerF.serialize();
        QString represent = triggerF.represent();
        auto varptr = ContextVarFabric::make<Trigger>(data);
        QCOMPARE(varptr->serialize(), data);
        QCOMPARE(varptr->represent(), represent);
    }
};

void context_variable_serializing(){
    namedvar_serializing();
    counter_serializing();
    trigger_serializing();
};
    // ^^^ Context Variables tests / Characters tests vvv
void player_serializing(){
    Player player;
    player.setName("Danila");
    player.setMood(Mood::Excited);
};

void character_serializing(){
    player_serializing();
}
    // ^^^ Character tests / Dialog stuff tests vvv
void dialognode_serializing(){
    constexpr int NodesCount = 400;

    QVector<DialogNode> nodes;
    nodes.reserve(NodesCount);

    for (int i = 0; i < NodesCount; ++i) {
        DialogNode node(
            QRandomGenerator::global()->bounded(1, 50000),  // parent
            QRandomGenerator::global()->bounded(1, 50000),  // event (allowed corner case)
            randomString(QRandomGenerator::global()->bounded(5, 40)),
            randomString(QRandomGenerator::global()->bounded(5, 40))
            );

        int variantsCount = QRandomGenerator::global()->bounded(0, 5);
        for (int v = 0; v < variantsCount; ++v) {
            DialogNode::variant_t variant(
                randomString(QRandomGenerator::global()->bounded(3, 20)),
                static_cast<DialogNode::id_type>(
                    QRandomGenerator::global()->bounded(0, NodesCount)
                    )
                );
            node.addVariant(variant);
        }

        nodes.push_back(node);
    }

    for (int i = 0; i < nodes.size(); ++i) {
        const DialogNode& original = nodes.at(i);

        QByteArray serialized = original.serialize();
        QVERIFY(!serialized.isEmpty());

        DialogNode restored(serialized);
        QByteArray reserialized = restored.serialize();

        QCOMPARE(reserialized, serialized);

        QString repr = original.represent();
        QVERIFY(!repr.isEmpty());

        QStringList tokens = repr.split(Entity::separator, Qt::KeepEmptyParts);
        DialogNode restored2(tokens);

        QString repr2 = restored2.represent();
        QCOMPARE(repr2, repr);
    }
}

void dialog_serializing(){
    dialognode_serializing();
};

};

/**
 * @brief EngineTest::EngineTest
 * @param parent
 */
EngineTest::EngineTest(QObject *parent)
    : QObject{parent}
{}

/**
 * @brief EngineTest::test_serializing
 */
void EngineTest::test_serializing()
{
    context_variable_serializing();
    dialog_serializing();
}

/**
 * @brief EngineTest::test_id_counting
 */
void EngineTest::test_id_counting()
{

}

/**
 * @brief EngineTest::test_OSG
 */
void EngineTest::test_OSG()
{

}
