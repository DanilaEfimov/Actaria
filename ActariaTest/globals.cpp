#include "enginetest.h"
#include "testutils.h"
#include "globals.h"

#include "Entities/context.h"
#include "Entities/scene.h"
#include "Entities/character.h"
#include "Entities/player.h"
#include "contextvarfabric.h"

#include "Entities/Operators/returnoperator.h"
#include "Entities/Operators/jumpoperator.h"

Context context = Context();

Character Hermiona = Character("Hermiona", Mood::Angry);
Character Ron = Character("Ron", Mood::Scared);

Player& Harry = Player::instance();

auto initContext = []() -> bool {

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

    for(int i = 0; i < count; i++) {
        QString name = QString("character%1").arg(QString::number(i));
        Mood mood = static_cast<Mood>(QRandomGenerator().bounded(static_cast<int>(Mood::Unknown)));
        Character character = Character(name, mood);
        context.addCharacter(character);
    }

    qDebug() << "initContext: global test context initialized.";

    return true;
}();

auto initPlayer = []() -> bool {

    Harry.setName("Harry");
    Harry.setMood(Mood::Scared);

    Context& experience = Player::getExperience();
    experience.addCharacter(Hermiona);
    experience.addCharacter(Ron);
    experience.addVariable(ContextVariableFabric::make_trigger("Hermiona_calmed", false));
    experience.addVariable(ContextVariableFabric::make_counter("failed_tryes", 2));
    experience.addVariable(ContextVariableFabric::make_namevar("stop_word", QString("please")));

    qDebug() << "initPlayer: global test player initialized";

    return true;
}();

Scene scene = Scene({});

auto initScene = []() -> bool {

    Event start_handler = Event();
    Event badway_handler = Event();

    DialogNode start = DialogNode(UNDEFINED_ID, start_handler.getId(), Hermiona.getId(),
        "Ron, if brains were given out for bravery, you’d still walk away empty-handed — you didn’t even try to think");
    DialogNode badWay = DialogNode(start.getId(), UNDEFINED_ID, Harry.getId(),
        "Well, at least I try, Hermione… which is more than I can say for some know-it-alls.");
    DialogNode goodWay = DialogNode(start.getId(), badway_handler.getId(), Harry.getId(),
        "Alright, you two, let’s each get three words, then coffee!");

    badway_handler.addOpertor(std::unique_ptr<JumpOperator>(new JumpOperator(badWay.getId())));
    start_handler.addOpertor(std::unique_ptr<ReturnOperator>(new ReturnOperator()));

    Dialog* dialog = new Dialog();
    dialog->addNode(std::make_unique<DialogNode>(start));
    dialog->addNode(std::make_unique<DialogNode>(badWay));
    dialog->addNode(std::make_unique<DialogNode>(goodWay));
    dialog->setRoot(start.getId());

    std::unique_ptr<Dialog> dlgp(dialog);
    scene = Scene(std::move(dlgp));

    scene.getDialog()->addEvent(std::make_unique<Event>(std::move(start_handler)));
    scene.getDialog()->addEvent(std::make_unique<Event>(std::move(badway_handler)));

    scene.getMeta().setDescription("It's a some school room");
    scene.getMeta().setSoundPath("C:/Actaria/MyProject/assets/sounds/scene1.mp3");
    scene.getMeta().setBackgroundPath("C:/Actaria/MyProject/assets/images/back1.png");

    qDebug() << "initScene: global test scene initialized.";

    return true;
}();
