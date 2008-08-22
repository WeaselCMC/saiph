#ifndef DOOR_H
/* defines */
#define DOOR_H
/* priorities */
#define DOOR_OPEN_PRIORITY 150
/* messages */
#define DOOR_DOOR_LOCKED "  This door is locked.  "
#define DOOR_UNLOCK_IT "  Unlock it? [yn] (n)  "

/* forward declare */
class Door;

/* includes */
#include <string>
#include "../Analyzer.h"
#include "../Globals.h"
#include "../Point.h"
#include "../Saiph.h"

/* namespace */
using namespace std;

/* analyzes the map and finds somewhere to explore */
class Door : public Analyzer {
	public:
		/* constructors */
		Door(Saiph *saiph);

		/* methods */
		void analyze();
		void complete();
		void parseMessages(const string &messages);

	private:
		/* variables */
		Saiph *saiph;
		string command2;
		Point cur_door;
		int sequence;
		unsigned char unlock_tool_key;

		/* methods */
		void findUnlockingTool();
};
#endif
