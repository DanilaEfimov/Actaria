#include "enginetest.h"
#include "testutils.h"
#include "readwrite.h"
#include "contextvarfabric.h"
#include "utils.h"

#include "entity.ser"

#include "trigger.ser"
#include "counter.ser"
#include "namevar.ser"

#include "operator.ser"
#include "assignmentoperator.ser"
#include "returnoperator.ser"
#include "calloperator.ser"
#include "whileoperator.ser"

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

void EngineTest::test_utils_processing()
{

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
        QVERIFY(utils::compare(original.getValue(), restored.getValue()));
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
        QVERIFY(utils::compare(original.getValue(), restored.getValue()));
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
        QVERIFY(utils::compare(original.getValue(), restored.getValue()));
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

        utils::compare(true, variable.second->getValue());
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
    this->next_operator_serializing();
    this->assignment_operator_serializing();
}

void EngineTest::jump_operator_serializing()
{

}

void EngineTest::call_operator_serializing()
{
    QList<Entity::id_type> ids = {
        0,
        1,
        42,
        UNDEFINED_ID,
        std::numeric_limits<Entity::id_type>::max(),
        std::numeric_limits<Entity::id_type>::min()
    };

    for(auto id : ids) {

        CallOperator op(id);
        CallOperator restored(UNDEFINED_ID);

        QByteArray buffer;

        QDataStream out(&buffer, QDataStream::WriteOnly);
        abi::write<CallOperator, EngineInfo::defaultVersion>(out, op);

        QDataStream in(&buffer, QIODevice::ReadOnly);
        abi::read<CallOperator, EngineInfo::defaultVersion>(in, restored);

        QCOMPARE(op.id, restored.id);
        QCOMPARE(op.event, restored.event);

        StringListCursor strbuffer;

        abi::write<CallOperator, EngineInfo::defaultVersion>(strbuffer, op);

        strbuffer.reset();
        abi::read<CallOperator, EngineInfo::defaultVersion>(strbuffer, restored);

        QCOMPARE(op.id, restored.id);
        QCOMPARE(op.event, restored.event);
    }
}

void EngineTest::next_operator_serializing()
{

}

/**
 * @brief EngineTest::return_operator_serializing
 *
 * Return operator is a special deriver of Operator.
 * Object of same type have not any own fields.
 */
void EngineTest::return_operator_serializing()
{
    ReturnOperator op;
    ReturnOperator restored;

    QByteArray buffer;

    QDataStream out(&buffer, QDataStream::WriteOnly);
    abi::write<ReturnOperator, EngineInfo::defaultVersion>(out, op);

    DEBUG_ONLY(
        qDebug() << "\n\treturn operator dump:\n\t" << buffer.toHex(' ');
        );

    QDataStream in(&buffer, QIODevice::ReadOnly);
    abi::read<ReturnOperator, EngineInfo::defaultVersion>(in, restored);

    QVERIFY(op.id == restored.id);

    StringListCursor strbuffer;

    abi::write<ReturnOperator, EngineInfo::defaultVersion>(strbuffer, op);

    strbuffer.reset();
    abi::read<ReturnOperator, EngineInfo::defaultVersion>(strbuffer, restored);

    QVERIFY(op.id == restored.id);
}

void EngineTest::while_operator_serializing()
{
    QList<Entity::id_type> ids = {
        0,
        1,
        42,
        UNDEFINED_ID,
        std::numeric_limits<Entity::id_type>::max(),
        std::numeric_limits<Entity::id_type>::min()
    };

    for (auto id1 : ids) {
        for (auto id2 : ids) {

            WhileOperator op(id1, id2);
            WhileOperator restored(UNDEFINED_ID, UNDEFINED_ID);

            QByteArray buffer;
            QDataStream out(&buffer, QDataStream::WriteOnly);
            abi::write<WhileOperator, EngineInfo::defaultVersion>(out, op);

            QDataStream in(&buffer, QIODevice::ReadOnly);
            abi::read<WhileOperator, EngineInfo::defaultVersion>(in, restored);

            QCOMPARE(op.id, restored.id);
            QCOMPARE(op.body, restored.body);
            QCOMPARE(op.toCompare, restored.toCompare);

            StringListCursor strbuffer;
            abi::write<WhileOperator, EngineInfo::defaultVersion>(strbuffer, op);

            strbuffer.reset();
            abi::read<WhileOperator, EngineInfo::defaultVersion>(strbuffer, restored);

            QCOMPARE(op.id, restored.id);
            QCOMPARE(op.body, restored.body);
            QCOMPARE(op.toCompare, restored.toCompare);
        }
    }
}

void EngineTest::condition_operator_serializing()
{

}

void EngineTest::assignment_operator_serializing()
{
    AssignmentOperator restored(UNDEFINED_ID, {});

    QRandomGenerator* generator = QRandomGenerator::global();

    for(auto& variable : context.variables) {

        AssignmentOperator op(variable.second->id,
            [&]() -> ContextValue {
            switch(variable.second->type()){
                case VarType::Counter: return generator->bounded(0x7FFFFFFF);
                case VarType::Name: return randomString(16);
                case VarType::Trigger: return variable.first % 2 ? true : false;
                default:
                    return -1;
            }
        }());

        QByteArray buffer;

        QDataStream out(&buffer, QDataStream::WriteOnly);
        abi::write<AssignmentOperator, EngineInfo::defaultVersion>(out, op);

        QDataStream in(&buffer, QIODevice::ReadOnly);
        abi::read<AssignmentOperator, EngineInfo::defaultVersion>(in, restored);

        QCOMPARE(op.lvalue, restored.lvalue);
        QVERIFY(utils::compare(op.rvalue, restored.rvalue));

        StringListCursor strbuffer;

        abi::write<AssignmentOperator, EngineInfo::defaultVersion>(strbuffer, op);

        strbuffer.reset();
        abi::read<AssignmentOperator, EngineInfo::defaultVersion>(strbuffer, restored);

        QCOMPARE(op.lvalue, restored.lvalue);
        QVERIFY(utils::compare(op.rvalue, op.rvalue));
    }
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

        QVERIFY(utils::compare(op.rvalue, variable.second->getValue()));
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
