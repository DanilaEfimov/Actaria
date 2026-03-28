import Harry;
import Hermione;
import Ron;

bool DracoMeeted = false;

character unknown;

scene Hogwarts {
    string description = "You, Harry, Hermione, and Ron are walking through the halls of Hogwarts, enjoying a break from classes.";
    string background = "C:/users/me/images/hogwarts_hallway.png";
    int player_mood = 1;

    mark start:
        Harry.speak("What a day, huh? The classes are so tiring.");
    options {
        "Yeah, I’m exhausted... Let's grab a snack.";
        "I don't mind. I just want to relax for a bit.";
    }

    mark after_start_tired: start.1:
        Hermione.speak("I know, I feel the same. Maybe we should visit the kitchen?");
    options {
        "Good idea, I could really use some pumpkin pasties.";
        "I’m fine for now, but later I could go for something sweet.";
    }

    mark after_start_relax: start.2:
        Ron.speak("We could sit by the fireplace in the common room. That sounds nice.");
    options {
        "That sounds perfect. Let’s go there.";
        "Maybe some time outside would be better, like by the lake.";
    }

    mark after_start_mention_draco: after_start_tired.2:
        Harry.speak("I just heard Draco Malfoy talking about the Slytherin Quidditch team... Do you think we should join the match next week?");
    options {
        "Draco? I hope we beat him at the match.";
        "I’m not sure. He’s always so smug, I don't think I want to play with him.";
    }

    mark after_draco_appears: after_start_mention_draco.1:
        Ron.speak("Oh no, here he comes... Draco!");
    options {
        "Draco, what do you want this time?";
        "What’s going on, Malfoy?";
    }

    mark after_meeting_draco: after_draco_appears.1:
        Draco.speak("Well, well... Looks like you three are up to no good again. Just wanted to remind you that Slytherin is going to win the Cup this year.");
    options {
        "We’ll see about that, Draco. We’re going to beat you this time.";
        "You’re full of yourself as always, Malfoy.";
    }

    mark after_skip_draco: after_start_mention_draco.2:
        Ron.speak("Let's just ignore him, he’s not worth our time.");
    options {
        "Good idea. Let’s just go to the common room.";
        "Right. He’s always so annoying.";
    }

    mark after_meeting_hermione: after_start_relax.1:
        Hermione.speak("Hey, I’ve been thinking... maybe we could study for the Potions test together later?");
    options {
        "Sure, I could use some help with that.";
        "I think I need a break from studying, but maybe later.";
    }
}

setEvent(after_start_mention_draco) {
    DracoMeeted = true;
    jmp after_meeting_draco;
}

setEvent(open_door) {
    if (DracoMeeted) {
        jmp after_meeting_draco;
    } else {
        jmp unknown_character;
    }
}

setEvent(unknown_character) {
    unknown.speak("Hey, I don’t recognize you. Who are you?");
    options {
        "I’m just here to see what’s behind the door...";
        "I think I’m lost, can you help me?";
    }
}
