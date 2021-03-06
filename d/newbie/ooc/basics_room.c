#include <std.h>

inherit ROOM;

void create() {
        ::create();
        set_property("indoors",1);
        set_property("no teleport",1);
        set_travel(PAVED_ROAD);
        set_terrain(VILLAGE);
        set_property("light",2);
        set_property("no sticks",1);
	set_property("ooc room", 1);
        set_short("%^MAGENTA%^Basic playing info. room");
        set_long(
@STYX
This room is designed to help players learn the basic and more useful commands used in Shadowgate.  There are several posters on the walls here to help you with syntax and hopefully answer many common questions for newcomers.  Type %^BOLD%^<look posters>%^RESET%^ to see the topics they cover and how to read them. 
STYX
        );
        set_smell("default","The room smells like freshly ground cinnamon.");
        set_listen("default","The room is quiet except for the conversations about how to play in ShadowGate.");
        set_items(([
        ]));
        set_exits(([
        "out" : "/d/newbie/ooc/hub_room2",
        ]));
}

void reset() {
	::reset();
	if(!present("posters")) 
	new ("/d/newbie/ooc/basics_poster")->move(TO);
}
