#include <std.h>
#include <spell.h>
#include <magic.h>
#include <rooms.h>

inherit SPELL;

int mylevel;
object portal;
string roomName;

void create() {
    ::create();
    set_spell_name("create demiplane");
    set_spell_level(([ "mage" : 8,"oracle":8 ]));
    set_mystery("elemental");
    set_spell_sphere("conjuration_summoning");
    set_syntax("cast CLASS genesis");
    set_description("You create a small, finite demiplane within astral and able to shape and control and reshape it to your liking.

Inside the plane you have access to the next commands:

%^ORANGE%^<set plane long %^ORANGE%^%^ULINE%^DESCRIPTION%^RESET%^%^ORANGE%^>%^RESET%^

  Will change the plane's long description to %^ORANGE%^%^ULINE%^DESCRIPTION%^RESET%^.

%^ORANGE%^<set plane short %^ORANGE%^%^ULINE%^DESCRIPTION%^RESET%^%^ORANGE%^>%^RESET%^

  Will change the plane's short description to %^ORANGE%^%^ULINE%^DESCRIPTION%^RESET%^.

%^ORANGE%^<set plane smell %^ORANGE%^%^ULINE%^DESCRIPTION%^RESET%^%^ORANGE%^>%^RESET%^

  Will change the plane's smells to %^ORANGE%^%^ULINE%^DESCRIPTION%^RESET%^.

%^ORANGE%^<set plane listen %^ORANGE%^%^ULINE%^DESCRIPTION%^RESET%^%^ORANGE%^>%^RESET%^

  Will change the plane's sounds to %^ORANGE%^%^ULINE%^DESCRIPTION%^RESET%^.

%^ORANGE%^<set plane seal on|off>%^RESET%^

  Will seal or unseal plane from inter dimensional travel. By default seal is on.

%^ORANGE%^<feature add %^ORANGE%^%^ULINE%^NAME%^RESET%^%^ORANGE%^ as %^ORANGE%^%^ULINE%^DESCRIPTION%^RESET%^%^ORANGE%^>%^RESET%^

  Will add feature with the %^ORANGE%^%^ULINE%^NAME%^RESET%^ and %^ORANGE%^%^ULINE%^DESCRIPTION%^RESET%^. You can then %^ORANGE%^<look %^ORANGE%^%^ULINE%^NAME%^RESET%^%^ORANGE%^>%^RESET%^ to see it.

%^ORANGE%^<feature remove %^ORANGE%^%^ULINE%^NAME%^RESET%^%^ORANGE%^>%^RESET%^

  Will remove feature with the %^ORANGE%^%^ULINE%^NAME%^RESET%^.

%^ORANGE%^<feature list>%^RESET%^

  Will list all added features.

%^ORANGE%^<feature clear>%^RESET%^

  Will remove all features.
");
    set_verbal_comp();
    set_somatic_comp();
    set_helpful_spell(1);
}

void spell_effect(int prof)
{
    if(!objectp(caster) || !objectp(place))
    {
        dest_effect();
        return;
    }
    if (place->query_property("no pocket space")) {
        tell_object(caster, "Something is interferring with your power.");
        if(objectp(TO)) TO->remove();
        return 0;
    }
    portal = new("/d/magic/obj/demiplane_portal");

    //messages here

    spell_successful();
    roomName = base_name(place);
    portal->set_property("spell", TO );
    portal->set_property("spelled", ({TO}) );
    portal->set_spellobj(TO);
    portal->start_magic(place,roomName);
    portal->move(place);

    tell_object(caster,"%^ORANGE%^You snap your fingers and a very %^ORANGE%^old, %^ORANGE%^eerie %^ORANGE%^d%^BOLD%^%^ORANGE%^o%^RESET%^%^ORANGE%^or%^ORANGE%^ appears.");
    tell_room(place,"%^ORANGE%^"+caster->QCN+" snaps "+caster->QP+" fingers and a very %^ORANGE%^old, %^ORANGE%^eerie %^ORANGE%^d%^BOLD%^%^ORANGE%^o%^RESET%^%^ORANGE%^or%^ORANGE%^ appears.",caster);

    //Portal poofs in message

    addSpellToCaster();
}

void dest_effect() {
	if(!objectp(portal))
	{
		::dest_effect();
        if(objectp(TO))
            TO->remove();
		return;
	}

    portal->end_magic();
    if(!objectp(place))
        place = find_object_or_load(roomName);

    //Poof message

    portal->move(ROOM_VOID);
    portal->remove();

    ::dest_effect();
    if(objectp(TO))
        TO->remove();
}
