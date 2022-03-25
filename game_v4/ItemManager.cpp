//
//  ItemManager.cpp
//

#include "ItemManager.h"

#include <cassert>
#include <string>
#include <iostream>

#include "Location.h"
#include "Item.h"

using namespace std;

static const unsigned int NO_SUCH_ITEM = 999999999;



ItemManager :: ItemManager (const string& game_name)
{
	//initBlizzard();
	initGhostwood();

	assert(isInvariantTrue());
}



unsigned int ItemManager :: getCount () const
{
	assert(isInvariantTrue());

	return ITEM_COUNT;
}

int ItemManager :: getScore () const
{
	assert(isInvariantTrue());

	int score = 0;
	for(unsigned int i = 0; i < ITEM_COUNT; i++)
	{
		score += items[i].getPlayerPoints();
	}
	return score;
}

void ItemManager :: printAtLocation (const Location& location) const
{
	assert(isInvariantTrue());

	for(unsigned int i = 0; i < ITEM_COUNT; i++)
	{
		if(items[i].isAtLocation(location))
			items[i].printDescription();
	}
}

void ItemManager :: printInventory () const
{
	assert(isInvariantTrue());

	for(unsigned int i = 0; i < ITEM_COUNT; i++)
	{
		if(items[i].isInInventory())
			items[i].printDescription();
	}
}

bool ItemManager :: isInInventory (char id)
{
	assert(isInvariantTrue());

	unsigned int item_index = find(id);

	if(item_index == NO_SUCH_ITEM)
		return false;
	else
		return items[item_index].isInInventory();
}



void ItemManager :: reset ()
{
	assert(isInvariantTrue());

	for(unsigned int i = 0; i < ITEM_COUNT; i++)
	{
		items[i].reset();
	}

	assert(isInvariantTrue());
}

void ItemManager :: take  (char id, const Location& player_location)
{
	assert(isInvariantTrue());

	unsigned int item_index = find(id);

	if(item_index != NO_SUCH_ITEM &&
	   items[item_index].isAtLocation(player_location))
	{
		items[item_index].moveToInventory();
	}
	else
		cout << "Invalid item." << endl;

	assert(isInvariantTrue());
}

void ItemManager :: leave (char id, const Location& player_location)
{
	assert(isInvariantTrue());

	unsigned int item_index = find(id);

	if(item_index != NO_SUCH_ITEM &&
	   items[item_index].isInInventory())
	{
		items[item_index].moveToLocation(player_location);
	}
	else
		cout << "Invalid item." << endl;

	assert(isInvariantTrue());
}



unsigned int ItemManager :: find (char id) const
{
	// linear search
	for(unsigned int i = 0; i < ITEM_COUNT; i++)
	{
		if(items[i].getId() == id)
			return i;
	}

	// found nothing
	return NO_SUCH_ITEM;
}

void ItemManager :: initBlizzard ()
{
	assert(ITEM_COUNT == 5);

	items[0] = Item('a', Location(6), 1,
	                "You see Alice (a) trying to read a very small compass.",
	                "Somewhere nearby, you hear Alice (a) jabbering about directions.");
	items[1] = Item('c', Location(6), 1,
	                "You see Charlie (c) lying half-buried in the drifting snow.",
	                "Behind you, Charlie (c) is dragging himself through the snow.");
	items[2] = Item('e', Location(25), 1,
	                "Young Emma (e) is crouched down, out of the wind.",
	                "Young Emma (e) is trying to use you to block the wind.");
	items[3] = Item('d', Location(29), 1,
	                "David (d) is using a stick to write in the snow here.",
	                "David (d) is dashing this way and that, despite the weather.");
	items[4] = Item('b', Location(39), 2,
	                "The twins, Benny and Bobby (b), are huddled together here.",
	                "The twins, Benny and Bobby (b), are huddled behind you.");
}

void ItemManager :: initGhostwood ()
{
	assert(ITEM_COUNT == 9);

	items[0] = Item('s', Location(3), -5,
	                "There is a black scarab beetle (s) here.",
	                "A black scarab beetle (s) is crawling up your arm.");
	items[1] = Item('c', Location(7), 9,
	                "There is a silver candlestick (c) here.",
	                "You are carrying a silver candlestick (c).");
	items[2] = Item('k', Location(13), 3,
	                "There is an old iron key (k) here.",
	                "You have an old iron key (k) in your pocket.");
	items[3] = Item('t', Location(19), -8,
	                "There is a tarantula (t) here.",
	                "There is a tarantula (t) hanging on your shirt.");
	items[4] = Item('b', Location(22), 4,
	                "There is a book (b) here with an eye drawn on the cover.",
	                "You have a book (b) under your arm with an eye drawn on the cover.");
	items[5] = Item('m', Location(37), -2,
	                "There is a giant moth (m) sleeping here.",
	                "A giant moth (m) is perched on your shoulder.");
	items[6] = Item('p', Location(52), 7,
	                "There is a golden pendant (p) here.",
	                "You are wearing a golden pendant (p).");
	items[7] = Item('d', Location(53), 1,
	                "There is a rune-carved dagger (d) here.",
	                "You have a rune-carved dagger (d) stuck in your belt.");
	items[8] = Item('r', Location(58), 10,
	                "There is a diamond ring (r) here.",
	                "You are wearing a diamond ring (r).");
}

bool ItemManager :: isInvariantTrue () const
{
	for(unsigned int i = 0; i < ITEM_COUNT; i++)
	{
		if(!items[i].isInitialized())
			return false;
	}
	return true;
}
