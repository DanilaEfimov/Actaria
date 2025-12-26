#define ACTARIA_TEST

#include "enginetest.h"
#include "testutils.h"
#include "namevar.h"
#include "counter.h"
#include "trigger.h"
#include "player.h"

namespace {

static constexpr abi::Version currentVersion = EngineInfo::defaultVersion;

    // Context Variables tests vvv
void namedvar_serializing()
{
    QStringList names = {
        "Danila", "", "-1201-20*@&#&!@%#!&", "Данила",
        "Lg&Fw3[09F0p#*fyO8&fuhp#(F-0_3F9_(*#f#f_#8F_f"
    };

    for(int i = 0; i < 20; i++){
        int size_inc = (i*i + 7*i + 10) % 100;
        names.append(randomString(10 + size_inc));
    }

    for(const auto& name : names){
        NameVar variable(name, randomString(10)); // value, name

        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        abi::write<NameVar, currentVersion>(out, variable);

        NameVar restored;
        QDataStream in(data);
        abi::read<NameVar, currentVersion>(in, restored);

        QCOMPARE(restored.getValue(), variable.getValue());
        QCOMPARE(restored.getName(), variable.getName());
        QCOMPARE(restored.getId(), variable.getId());

        QStringList list;
        abi::write<NameVar, currentVersion>(list, variable);

        NameVar restored2;
        abi::read<NameVar, currentVersion>(list, restored2);

        QCOMPARE(restored2.getValue(), variable.getValue());
        QCOMPARE(restored2.getName(), variable.getName());
        QCOMPARE(restored2.getId(), variable.getId());
    }
}


void counter_serializing() {
    QList<int> values = {0, 1, -1, INT_MAX, INT_MIN};
    for(int i = 0; i < 20; i++){
        values.append(i*i*i*i + 0xFFFF);
    }

    for(const auto& value : values){
        Counter variable(value, randomString(10));

        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        abi::write<Counter, currentVersion>(out, variable);

        Counter restored;
        QDataStream in(data);
        abi::read<Counter, currentVersion>(in, restored);

        QCOMPARE(restored.getValue(), variable.getValue());
        QCOMPARE(restored.getName(), variable.getName());
        QCOMPARE(restored.getId(), variable.getId());

        QStringList list;
        abi::write<Counter, currentVersion>(list, variable);

        Counter restored2;
        abi::read<Counter, currentVersion>(list, restored2);

        QCOMPARE(restored2.getValue(), variable.getValue());
        QCOMPARE(restored2.getName(), variable.getName());
        QCOMPARE(restored2.getId(), variable.getId());
    }
}


void trigger_serializing()
{
    QList<bool> values = {true, false};

    for(const auto& value : values){
        Trigger variable(value, "game_trigger");

        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        abi::write<Trigger, currentVersion>(out, variable);

        Trigger restored;
        QDataStream in(data);
        abi::read<Trigger, currentVersion>(in, restored);

        QCOMPARE(restored.getValue(), variable.getValue());
        QCOMPARE(restored.getName(), variable.getName());
        QCOMPARE(restored.getId(), variable.getId());

        QStringList list;
        abi::write<Trigger, currentVersion>(list, variable);

        Trigger restored2;
        abi::read<Trigger, currentVersion>(list, restored2);

        QCOMPARE(restored2.getValue(), variable.getValue());
        QCOMPARE(restored2.getName(), variable.getName());
        QCOMPARE(restored2.getId(), variable.getId());
    }
}


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
