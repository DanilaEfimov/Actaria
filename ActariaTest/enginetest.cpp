#include "enginetest.h"
#include "testutils.h"
#include "readwrite.h"
#include "contextvarfabric.h"

#include "entity.ser"

#include "trigger.ser"
#include "counter.ser"
#include "namevar.ser"

#include "operator.ser"
#include "assignmentoperator.ser"

#include "Entities/context.h"

#include "Entities/scene.h"

#include "Errors/nosuchid.h"

#include <QByteArray>


namespace {

static Context context;
static Scene scene({});

static auto initContext = []() -> bool {

    int count = 100;
    for(int i = 0; i < count; i++) {
        QString name = QString("trigger%1").arg(QString::number(i));
        bool value = QRandomGenerator().bounded(10) ? true : false;
        context.addVariable(std::make_unique<Trigger>(value, name));
    }

    for(int i = 0; i < count; i++) {
        QString name = QString("counter%1").arg(QString::number(i));
        int value = QRandomGenerator().bounded(1000);
        context.addVariable(std::make_unique<Counter>(value, name));
    }

    for(int i = 0; i < count; i++) {
        QString name = QString("named%1").arg(QString::number(i));
        QString value = randomString(5 + i % 12);
        context.addVariable(std::make_unique<NameVar>(value, name));
    }

    qDebug() << "initContext: global test context initialized.";

    return true;
}();

static auto initScene = []() -> bool {

    qDebug() << "initScene: global test scene initialized.";

    return true;
}();

};

EngineTest::EngineTest(QObject *parent)
    : QObject(parent)
{}

void EngineTest::test_serializing()
{
    this->context_serializing();
    this->context_variable_serializing();
    this->operators_serializing();
}

void EngineTest::test_processing()
{
    this->operators_processing();
}

void EngineTest::test_id_counting()
{

}

void EngineTest::test_context_algebra()
{

}

void EngineTest::test_OSG()
{

}

void EngineTest::namedvar_serializing()
{
    constexpr int count = 50;

    for (int i = 0; i < count; ++i) {
        QString name  = QString("namevar_%1").arg(i);
        QString value = randomString(5 + i % 10);

        if(i == 0)      value = "";
        else if(i == 1) value = "VERY_VERY_LARGE_CONTEXT_VARIABLE_VALUE_WHICH_WONT_BE_USED_IN_REALY_GAME";
        else if(i == 1) value = "st276 &6)S  s78 0 | |} | I~) I~|_W) |_)@|_ @U|E("; // strange unreadable value

        NameVar original(value, name);
        NameVar restored;

        QByteArray buffer;

        {
            QDataStream out(&buffer, QIODevice::WriteOnly);
            abi::write<NameVar, EngineInfo::defaultVersion>(out, original);
        }

        {
            QDataStream in(&buffer, QIODevice::ReadOnly);
            abi::read<NameVar, EngineInfo::defaultVersion>(in, restored);
        }

        QCOMPARE(restored.type(), VarType::Name);
        QCOMPARE(restored.hash(), original.hash());
        QCOMPARE(QString(restored), QString(original));
        QCOMPARE(
            std::get<NameVar::value_type>(restored.getValue()),
            std::get<NameVar::value_type>(original.getValue())
            );
        QCOMPARE(restored.getName(), original.getName());
    }
}

void EngineTest::counter_serializing()
{
    constexpr int count = 50;

    for (int i = 0; i < count; ++i) {
        QString name  = QString("counter_%1").arg(i);
        int value = QRandomGenerator().bounded(10000);

        if(i == 0)      value = 0xFFFFFFFF;
        else if(i == 1) value = 0xF0F0F0F0;
        else if(i == 1) value = 0x00000000;

        Counter original(value, name);
        Counter restored;

        QByteArray buffer;

        {
            QDataStream out(&buffer, QIODevice::WriteOnly);
            abi::write<Counter, EngineInfo::defaultVersion>(out, original);
        }

        {
            QDataStream in(&buffer, QIODevice::ReadOnly);
            abi::read<Counter, EngineInfo::defaultVersion>(in, restored);
        }

        QCOMPARE(restored.type(), VarType::Counter);
        QCOMPARE(restored.hash(), original.hash());
        QCOMPARE(int(restored), int(original));
        QCOMPARE(
            std::get<Counter::value_type>(restored.getValue()),
            std::get<Counter::value_type>(original.getValue())
            );
        QCOMPARE(restored.getName(), original.getName());
    }
}

void EngineTest::trigger_serializing()
{
    constexpr int count = 50;

    for (int i = 0; i < count; ++i) {
        QString name  = QString("trigger_%1").arg(i);
        int value = i%2 ? true : false;

        Trigger original(value, name);
        Trigger restored;

        QByteArray buffer;

        {
            QDataStream out(&buffer, QIODevice::WriteOnly);
            abi::write<Trigger, EngineInfo::defaultVersion>(out, original);
        }

        {
            QDataStream in(&buffer, QIODevice::ReadOnly);
            abi::read<Trigger, EngineInfo::defaultVersion>(in, restored);
        }

        QCOMPARE(restored.type(), VarType::Trigger);
        QCOMPARE(restored.hash(), original.hash());
        QCOMPARE(bool(restored), bool(original));
        QCOMPARE(
            std::get<Trigger::value_type>(restored.getValue()),
            std::get<Trigger::value_type>(original.getValue())
            );
        QCOMPARE(restored.getName(), original.getName());
    }
}

void EngineTest::context_variable_serializing()
{
    this->namedvar_serializing();
    this->trigger_serializing();
    this->counter_serializing();
}

void EngineTest::context_variables_processing()
{
    QString nameValue = "";
    bool triggerValue = false;
    int counterValue = 0;

    QRandomGenerator* generator = QRandomGenerator::global();

    for(auto& variable : context.variables){
        VarType type = variable.second->type();
        switch(type){
        case VarType::Name:
            nameValue = randomString(8 + generator->bounded(8));
            variable.second->setValue(nameValue); break;
        case VarType::Counter:
            triggerValue = generator->bounded(10) % 2 ? true : false;
            variable.second->setValue(counterValue); break;
        case VarType::Trigger:
            counterValue = generator->bounded(0x0000FFFF);
            variable.second->setValue(triggerValue); break;
        default:
            qDebug() << "EngineTest::assignment_operator_serializing: undefined type";
        }

        compare(true, variable.second->getValue());
    }
}

void EngineTest::context_serializing()
{
    // Context copy;

    // QByteArray serialized;
    // {
    //     QDataStream out(&serialized, QIODevice::WriteOnly);
    //     abi::write<Context, EngineInfo::defaultVersion>(out, context);
    // }

    // {
    //     QDataStream in(&serialized, QIODevice::ReadOnly);
    //     abi::read<Context, EngineInfo::defaultVersion>(in, copy);
    // }

    // QCOMPARE(copy, context);

    // StringListCursor line;

    // abi::write<Context, EngineInfo::defaultVersion>(line, context);

    // abi::read<Context, EngineInfo::defaultVersion>(line, copy);

    // QCOMPARE(copy, context);
}

void EngineTest::player_serializing()
{

}

void EngineTest::character_serializing()
{

}

// ^^^ characters serializing / operators serializing vvv

void EngineTest::operators_serializing()
{
    this->return_operator_serializing();
    this->call_operator_serializing();
    this->while_operator_serializing();
    this->jump_operator_serializing();
    this->condition_operator_serializing();
    this->assignment_operator_serializing();
}

void EngineTest::jump_operator_serializing()
{

}

void EngineTest::call_operator_serializing()
{

}

void EngineTest::next_operator_serializing()
{

}

void EngineTest::return_operator_serializing()
{

}

void EngineTest::while_operator_serializing()
{

}

void EngineTest::condition_operator_serializing()
{

}

void EngineTest::assignment_operator_serializing()
{

}

// ^^^ operators serializing / operators processing vvv

void EngineTest::operators_processing()
{
    this->assignment_operator_processing();
}

void EngineTest::jump_operator_processing()
{

}

void EngineTest::call_operator_processing()
{

}

void EngineTest::next_operator_processing()
{

}

void EngineTest::return_operator_processing()
{

}

void EngineTest::while_operator_processing()
{

}

void EngineTest::condition_operator_processing()
{

}

void EngineTest::assignment_operator_processing()
{
    for(auto& variable : context.variables) {
        auto type = variable.second->type();
        AssignmentOperator op(variable.first, {});

        ContextValue assigned;
        switch(type){
        case VarType::Name: assigned = randomString(8 + QRandomGenerator().bounded(8)); break;
        case VarType::Counter: assigned = QRandomGenerator().bounded(0x0000FFFF); break;
        case VarType::Trigger: assigned = true; break;
        default: break;
        }

        op.rvalue = assigned;
        op.apply(context, scene);   // scene marked as gnu::unused

        QVERIFY(compare(op.rvalue, variable.second->getValue()));
    }

    try {

        AssignmentOperator op(UNDEFINED_ID, {});
        op.apply(context, scene);

    } catch(const NoSuchId& e) {
        qDebug() << "\n\t pseudo error catched \n\t"<< e.what();
    }

}

void EngineTest::dialognode_serializing()
{

}

void EngineTest::dialognode_variant_management()
{

}

void EngineTest::dialog_serializing()
{

}

void EngineTest::scene_serializing()
{

}
