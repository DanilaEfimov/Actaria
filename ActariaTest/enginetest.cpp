#include "enginetest.h"
#include "contextvarfabric.h"
#include "serializecharacters"
#include "dialognode.ser"
#include "testutils.h"
#include "Operators/assignmentoperator.h"
#include "Operators/jumpoperator.h"
#include "Operators/nextoperator.h"
#include "Operators/conditionoperator.h"
#include "Operators/whileoperator.h"
#include "Operators/returnoperator.h"
#include "Entities/scene.h"
#include <variant>


EngineTest::EngineTest(QObject *parent)
    : QObject(parent)
{}

// ---------------- Context Variables ----------------

void EngineTest::namedvar_serializing()
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
        NameVar variable(name, randomString(10));

        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        abi::write<NameVar, currentVersion>(out, variable);

        NameVar restored;
        QDataStream in(&data, QIODevice::ReadOnly);
        abi::read<NameVar, currentVersion>(in, restored);

        QCOMPARE(std::get<QString>(restored.getValue()), std::get<QString>(variable.getValue()));
        QCOMPARE(restored.getName(), variable.getName());
        QCOMPARE(restored.getId(), variable.getId());

        StringListCursor list;
        abi::write<NameVar, currentVersion>(list, variable);

        NameVar restored2;
        abi::read<NameVar, currentVersion>(list, restored2);

        QCOMPARE(std::get<QString>(restored2.getValue()), std::get<QString>(variable.getValue()));
        QCOMPARE(restored2.getName(), variable.getName());
        QCOMPARE(restored2.getId(), variable.getId());
    }
}

void EngineTest::counter_serializing()
{
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
        QDataStream in(&data, QIODevice::ReadOnly);
        abi::read<Counter, currentVersion>(in, restored);

        QCOMPARE(std::get<int>(restored.getValue()), std::get<int>(variable.getValue()));
        QCOMPARE(restored.getName(), variable.getName());
        QCOMPARE(restored.getId(), variable.getId());

        StringListCursor list;
        abi::write<Counter, currentVersion>(list, variable);

        Counter restored2;
        abi::read<Counter, currentVersion>(list, restored2);

        QCOMPARE(std::get<int>(restored2.getValue()), std::get<int>(variable.getValue()));
        QCOMPARE(restored2.getName(), variable.getName());
        QCOMPARE(restored2.getId(), variable.getId());
    }
}

void EngineTest::trigger_serializing()
{
    QList<bool> values = {true, false};

    for(const auto& value : values){
        Trigger variable(value, "game_trigger");

        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        abi::write<Trigger, currentVersion>(out, variable);

        Trigger restored;
        QDataStream in(&data, QIODevice::ReadOnly);
        abi::read<Trigger, currentVersion>(in, restored);

        QCOMPARE(std::get<bool>(restored.getValue()), std::get<bool>(variable.getValue()));
        QCOMPARE(restored.getName(), variable.getName());
        QCOMPARE(restored.getId(), variable.getId());

        StringListCursor list;
        abi::write<Trigger, currentVersion>(list, variable);

        Trigger restored2;
        abi::read<Trigger, currentVersion>(list, restored2);

        QCOMPARE(std::get<bool>(restored2.getValue()), std::get<bool>(variable.getValue()));
        QCOMPARE(restored2.getName(), variable.getName());
        QCOMPARE(restored2.getId(), variable.getId());
    }
}

void EngineTest::context_variable_serializing()
{
    namedvar_serializing();
    counter_serializing();
    trigger_serializing();
}

// ---------------- Characters ----------------

void EngineTest::player_serializing() {
    Player& player = Player::instance();
    Context& exp = player.experience;
    exp.clear();

    const int varCount = 50;
    for(int i = 0; i < varCount; ++i) {
        auto id = static_cast<Context::key_t>(i);
        std::unique_ptr<ContextVar> var;

        QString name = QString("NameVar%1").arg(i);
        switch(i % 3) {
        case 0: var = ContextVariableFabric::make_namevar(name, randomString(10)); break;
        case 1: var = ContextVariableFabric::make_counter(name, i); break;
        case 2: var = ContextVariableFabric::make_trigger(name, i % 2 == 0); break;
        }

        var->id = id;
        exp.set(id, var->getValue());
        exp.addVariable(std::move(var));
    }

    player.setName("Danila");
    player.setMood(Mood::Excited);

    for(int i = 0; i < 10; ++i) {
        QString charName = QString("Character%1").arg(i);
        Character c(charName, static_cast<Mood>(i % 4));
        player.experience.addCharacter(c);
    }

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    abi::write<Player, currentVersion>(out, player);

    Player restored;
    QDataStream in(&data, QIODevice::ReadOnly);
    abi::read<Player, currentVersion>(in, restored);

    QCOMPARE(restored.getName(), player.getName());
    QCOMPARE(restored.getMood(), player.getMood());

    const Context& restoredExp = restored.experience;
    QCOMPARE(restoredExp.size(), exp.size());

    for(int i = 0; i < varCount; ++i) {
        auto id = static_cast<Context::key_t>(i);
        auto valOrig = exp.getValue(utils::id_type(id));
        auto valRest = restoredExp.getValue(id);
        QVERIFY(compare(valOrig, valRest));
    }

    QByteArray serialized;
    StringListCursor list;
    abi::write<Player, currentVersion>(list, player);

    Player restored2;
    abi::read<Player, currentVersion>(list, restored2);

    QCOMPARE(restored2.getName(), player.getName());
    QCOMPARE(restored2.getMood(), player.getMood());
    QCOMPARE(restored2.experience.size(), exp.size());
}

void EngineTest::character_serializing()
{
    player_serializing();
}

// ---------------- Dialog ----------------

DialogNode root(UNDEFINED_ID, UNDEFINED_ID, UNDEFINED_ID, "Hello, World!");
void EngineTest::dialognode_serializing()
{
    QVector<DialogNode> nodes = {root};
    QSet<Entity::id_type> parents = {UNDEFINED_ID};

    for(int i = 0; i < 200; i++){
        DialogNode node(randomElement(parents), UNDEFINED_ID, UNDEFINED_ID,
                        randomString(QRandomGenerator::global()->bounded(20)));

        nodes[QRandomGenerator::global()->bounded(nodes.size())]
            .addVariant(DialogNode::variant_t(randomString(10), node.getId()));

        nodes.push_back(node);
        parents.insert(node.getId());
    }

    auto checkNode = [](const DialogNode& a, const DialogNode& b){
        QCOMPARE(a.getId(), b.getId());
        QCOMPARE(a.getMessage(), b.getMessage());
        QCOMPARE(a.getEventId(), b.getEventId());
        QCOMPARE(a.getFromCharacter(), b.getFromCharacter());
        QCOMPARE(a.variants, b.variants);
    };

    for(const auto& n : nodes){
        {
            QByteArray serialized;
            QDataStream out(&serialized, QIODevice::WriteOnly);
            abi::write<DialogNode, currentVersion>(out, n);

            DialogNode copy;
            QDataStream in(&serialized, QIODevice::ReadOnly);
            abi::read<DialogNode, currentVersion>(in, copy);

            checkNode(n, copy);
        }

        {
            StringListCursor original;
            abi::write<DialogNode, currentVersion>(original, n);

            DialogNode copy;
            abi::read<DialogNode, EngineInfo::defaultVersion>(original, copy);
            checkNode(n, copy);
        }
    }
}

void EngineTest::dialognode_variant_management()
{
}

void EngineTest::dialog_serializing()
{
    dialognode_serializing();
}

// ---------------- Scene ----------------

void EngineTest::scene_serializing()
{

}

// ---------------- Context ----------------

void EngineTest::context_serializing() {
    Context ctx;
    const int varCount = 300;
    QVector<QString> names;
    names.reserve(varCount);

    for(int i = 0; i < varCount; ++i) {
        names.append(randomString(12));
    }

    for(int i = 0; i < varCount; ++i) {
        auto id = static_cast<Context::key_t>(i);
        std::unique_ptr<ContextVar> var;

        switch(i % 3) {
        case 0: var = ContextVariableFabric::make_namevar(names[i], QString("val%1").arg(i)); break;
        case 1: var = ContextVariableFabric::make_counter(names[i], i); break;
        case 2: var = ContextVariableFabric::make_trigger(names[i], i % 2 == 0); break;
        }

        var->id = id;
        ctx.set(id, var->getValue());
        ctx.addVariable(std::move(var));
    }

    QCOMPARE(ctx.size(), varCount);

    for(int i = 0; i < varCount; ++i) {
        auto id = static_cast<Context::key_t>(i);
        QVERIFY(ctx.containsVariable(id));
        auto val = ctx.getValue(id);
        QVERIFY(!val.valueless_by_exception());

        switch(i % 3) {
        case 0: QCOMPARE(std::get<QString>(val), QString("val%1").arg(i)); break;
        case 1: QCOMPARE(std::get<int>(val), i); break;
        case 2: QCOMPARE(std::get<bool>(val), i % 2 == 0); break;
        }
    }

    for(int i = 0; i < varCount; i += 3) {
        auto id = static_cast<Context::key_t>(i);
        ctx.removeVariable(id);
    }

    for(int i = 0; i < varCount; ++i) {
        auto id = static_cast<Context::key_t>(i);
        if(i % 3 == 0) {
            QVERIFY(!ctx.containsVariable(id));
        } else {
            QVERIFY(ctx.containsVariable(id));
        }
    }

    QCOMPARE(ctx.size(), varCount - varCount / 3);

    QByteArray serialized;
    QDataStream out(&serialized, QIODevice::WriteOnly);
    abi::write<Context, currentVersion>(out, ctx);

    Context restored;
    QDataStream in(&serialized, QIODevice::ReadOnly);
    abi::read<Context, currentVersion>(in, restored);

    QCOMPARE(restored.size(), ctx.size());

    for(int i = 0; i < varCount; ++i) {
        auto id = static_cast<Context::key_t>(i);
        if(i % 3 == 0) continue;
        QVERIFY(restored.containsVariable(id));
        QVERIFY(compare(restored.getValue(id), ctx.getValue(id)));
    }
}

// ---------------- Private slots ----------------

void EngineTest::test_serializing()
{
    context_variable_serializing();
    character_serializing();
    dialog_serializing();
    context_serializing();
}

void EngineTest::test_id_counting()
{
}

void EngineTest::test_context_algebra()
{
    Context& context = Player::experience;
    context.clear();

    const int varCount = 100;

    std::unique_ptr<Dialog> dialog(new Dialog());
    dialog->nodes.addObj(&root);
    Scene dummyScene(std::move(dialog));

    struct VarInfo {
        ContextVar* var;
        ContextVar::ContextValue newValue;
    };

    QVector<VarInfo> vars;
    vars.reserve(varCount);

    for(int i = 0; i < varCount; ++i){
        auto typeSelector = i % 3;
        VarInfo info;

        switch(typeSelector){
        case 0: {
            int initial = QRandomGenerator::global()->bounded(1000);
            int newVal  = QRandomGenerator::global()->bounded(10000);
            info.var = ContextVariableFabric::make_counter(QString("Counter%1").arg(i), initial).release();
            info.newValue = newVal;
            break;
        }
        case 1: {
            bool initial = QRandomGenerator::global()->bounded(2);
            bool newVal  = QRandomGenerator::global()->bounded(2);
            info.var = ContextVariableFabric::make_trigger(QString("Trigger%1").arg(i), initial).release();
            info.newValue = newVal;
            break;
        }
        case 2: {
            QString initial = randomString(5 + QRandomGenerator::global()->bounded(10));
            QString newVal  = randomString(5 + QRandomGenerator::global()->bounded(10));
            info.var = ContextVariableFabric::make_namevar(QString("Name%1").arg(i), initial).release();
            info.newValue = newVal;
            break;
        }
        }

        info.var->id = i;
        context.addVariable(std::unique_ptr<ContextVar>(info.var));
        vars.push_back(std::move(info));
    }

    for(int i = 0; i < varCount; ++i){
        const auto& info = vars[i];
        int id = i;

        AssignmentOperator op(id, info.newValue);
        bool applied = op.apply(context, dummyScene);
        QVERIFY(applied);

        ContextVar::ContextValue val = context.getValue(id);
        std::visit([&](auto&& v){
            using T = std::decay_t<decltype(v)>;
            QVERIFY(v == std::get<T>(info.newValue));
        }, val);
    }

    JumpOperator jmp(UNDEFINED_ID);
    jmp.apply(context, dummyScene);

    Event event;
    ReturnOperator returnOp(&event);
    returnOp.apply(context, dummyScene);

    ConditionOperator condition(true, std::make_unique<Event>(), nullptr);
    condition.apply(context, dummyScene);

    context.variables.find(1)->second->setValue(false);
    WhileOperator whileOp(1, &event);
    whileOp.apply(context, dummyScene);
}

void EngineTest::test_OSG()
{
}
