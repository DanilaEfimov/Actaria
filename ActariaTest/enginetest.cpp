#include "enginetest.h"
#include "contextvarfabric.h"
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

        QCOMPARE(restored.getValue(), variable.getValue());
        QCOMPARE(restored.getName(), variable.getName());
        QCOMPARE(restored.getId(), variable.getId());

        StringListCursor list;
        abi::write<NameVar, currentVersion>(list, variable);

        NameVar restored2;
        abi::read<NameVar, currentVersion>(list, restored2);

        QCOMPARE(restored2.getValue(), variable.getValue());
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

        QCOMPARE(restored.getValue(), variable.getValue());
        QCOMPARE(restored.getName(), variable.getName());
        QCOMPARE(restored.getId(), variable.getId());

        StringListCursor list;
        abi::write<Counter, currentVersion>(list, variable);

        Counter restored2;
        abi::read<Counter, currentVersion>(list, restored2);

        QCOMPARE(restored2.getValue(), variable.getValue());
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

        QCOMPARE(restored.getValue(), variable.getValue());
        QCOMPARE(restored.getName(), variable.getName());
        QCOMPARE(restored.getId(), variable.getId());

        StringListCursor list;
        abi::write<Trigger, currentVersion>(list, variable);

        Trigger restored2;
        abi::read<Trigger, currentVersion>(list, restored2);

        QCOMPARE(restored2.getValue(), variable.getValue());
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

void EngineTest::player_serializing()
{
    Player player;
    player.setName("Danila");
    player.setMood(Mood::Excited);
}

void EngineTest::character_serializing()
{
    player_serializing();
}

// ---------------- Dialog ----------------

void EngineTest::dialognode_serializing()
{
    DialogNode root(UNDEFINED_ID, UNDEFINED_ID, UNDEFINED_ID, "Hello, World!");
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

            DialogNode copy(original);
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

// ---------------- Context ----------------

void EngineTest::context_serializing()
{
    Context ctx;

    const int varCount = 300;
    QVector<QString> names;
    names.reserve(varCount);

    for(int i = 0; i < varCount; ++i){
        names.append(randomString(12));
    }

    for(int i = 0; i < varCount; ++i){
        const QString& name = names[i];
        std::unique_ptr<ContextVar> var;

        switch(i % 3){
        case 0: var = ContextVariableFabric::make_namevar(name, QString("val%1").arg(i)); break;
        case 1: var = ContextVariableFabric::make_counter(name, i); break;
        case 2: var = ContextVariableFabric::make_trigger(name, i % 2 == 0); break;
        }

        ctx.addVariable(std::move(var));
    }

    QCOMPARE(ctx.size(), varCount);

    for(int i = 0; i < varCount; ++i){
        const QString& name = names[i];
        QVERIFY(ctx.containsVariable(name));

        auto val = ctx.getValue(name);
        QVERIFY(!val.valueless_by_exception());

        switch(i % 3){
        case 0: QCOMPARE(std::get<QString>(val), QString("val%1").arg(i)); break;
        case 1: QCOMPARE(std::get<int>(val), i); break;
        case 2: QCOMPARE(std::get<bool>(val), i % 2 == 0); break;
        }
    }

    for(int i = 0; i < varCount; i += 3){
        ctx.removeVariable(names[i]);
    }

    for(int i = 0; i < varCount; ++i){
        const QString& name = names[i];
        if(i % 3 == 0){
            QVERIFY(!ctx.containsVariable(name));
        } else {
            QVERIFY(ctx.containsVariable(name));
        }
    }

    QCOMPARE(ctx.size(), varCount - varCount/3);

    QByteArray serialized;
    QDataStream out(&serialized, QIODevice::WriteOnly);
    abi::write<Context, currentVersion>(out, ctx);

    Context restored;
    QDataStream in(&serialized, QIODevice::ReadOnly);
    abi::read<Context, currentVersion>(in, restored);

    QCOMPARE(restored.size(), ctx.size());
    for(int i = 0; i < varCount; ++i){
        const QString& name = names[i];
        if(i % 3 == 0) continue;
        QCOMPARE(restored.variables.at(name)->getValue(), ctx.variables.at(name)->getValue());
    }
}

// ---------------- Private slots ----------------

void EngineTest::test_serializing()
{
    context_variable_serializing();
    dialog_serializing();
    context_serializing();
}

void EngineTest::test_id_counting()
{
}

void EngineTest::test_OSG()
{
}
