#include "Amulet.h"
#include "../Globals.h"
#include "../Inventory.h"
#include "../World.h"
#include "../Actions/PutOn.h"
#include "../Actions/Remove.h"
#include "../Data/Amulet.h"
#include "../Events/Event.h"
#include "../Events/ChangedInventoryItems.h"
#include "../Events/ReceivedItems.h"

using namespace analyzer;
using namespace event;
using namespace std;

/* register analyzer */
int Amulet::id = World::registerAnalyzer(new Amulet());

/* constructors/destructor */
Amulet::Amulet() : Analyzer("Amulet") {
}

/* methods */
void Amulet::onEvent(Event *const event) {
	if (event->getID() == ReceivedItems::id) {
		ReceivedItems *e = (ReceivedItems *) event;
		wearAmulet(e->item_keys);
	} else if (event->getID() == ChangedInventoryItems::id) {
		ChangedInventoryItems *e = (ChangedInventoryItems *) event;
		wearAmulet(e->item_keys);
	}
}

/* private methods */
void Amulet::wearAmulet(const vector<unsigned char> &keys) {
	map<unsigned char, Item>::iterator worn = Inventory::items.find(Inventory::slots[SLOT_AMULET]);
	if (worn != Inventory::items.end() && worn->second.beatitude == CURSED)
		return; // wearing a cursed amulet, no point trying to wear another amulet

	/* find the best amulet */
	unsigned char best_key = (worn == Inventory::items.end()) ? '\0' : worn->first;
	map<string, data::Amulet *>::iterator best_amulet = (worn == Inventory::items.end()) ? data::Amulet::amulets.end() : data::Amulet::amulets.find(worn->second.name);

	for (vector<unsigned char>::const_iterator k = keys.begin(); k != keys.end(); ++k) {
		map<unsigned char, Item>::iterator i = Inventory::items.find(*k);
		if (i == Inventory::items.end())
			return; // huh? this can't happen
		map<string, data::Amulet *>::iterator a = data::Amulet::amulets.find(i->second.name);
		if (a == data::Amulet::amulets.end())
			return; // this is no amulet

		/* TODO: is this amulet better than the one we wear? */
		/* TODO: if we find a better amulet, take off current amulet and return */
	}

	if (best_key == '\0')
		return; // no new amulet to put on or wearing best amulet

	/* put on this amulet */
	setAction(new action::PutOn(best_key, 100));
}
