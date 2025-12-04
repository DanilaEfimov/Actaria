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
        QCOMPARE(varptr->represent(), data);
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
    // ^^^ Character tests / Dialog stuff tests vvv
void dialognode_serializing(){
    DialogNode node;
    node.setMessage("This is first scene in the game...");
};

void dialog_serializing(){

};

};

EngineTest::EngineTest(QObject *parent)
    : QObject{parent}
{}

void EngineTest::test_serializing()
{
    context_variable_serializing();
}

void EngineTest::test_id_counting()
{

}

void EngineTest::test_OSG()
{

}
