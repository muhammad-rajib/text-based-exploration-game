//
//  Main.cpp
//
//  Name: __________
//  Student Number: __________
//

#include <cassert>
#include <string>
#include <iostream>

#include "Location.h"
#include "World.h"
#include "Item.h"

using namespace std;

const bool WAIT_AT_END = true;

//
//  initAllItemsBlizzard
//
//  Purpose: To initialize the items in the specified array for
//           the Blizzard game.
//  Parameter(s):
//    <1> items: The array of items
//    <2> count: The number of items in the array
//  Precondition(s):
//    <1> count == 5
//  Returns: N/A
//  Side Effect: The Items in items are initialized as the items
//               for the game Blizzard.
//
static void initAllItemsBlizzard (Item items[],
                                  unsigned int count);

//
//  initAllItemsGhostwood
//
//  Purpose: To initialize the items in the specified array for
//           the Ghostwood game.
//  Parameter(s):
//    <1> items: The array of items
//    <2> count: The number of items in the array
//  Precondition(s):
//    <1> count == 9
//  Returns: N/A
//  Side Effect: The Items in items are initialized as the items
//               for the game Ghostwood.
//
static void initAllItemsGhostwood (Item items[],
                                   unsigned int count);

//
//  printItemsAtLocation
//
//  Purpose: To print all the items in the specified array that
//           are at the specified row and column.
//  Parameter(s):
//    <1> items: The items to print
//    <2> count: The number of items in the array
//    <3> location: The location to print items at
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The current description is printed for the
//               Items in items that are at location location.
//               The items array is assumed to contain count
//               elements.
//
static void printItemsAtLocation (const Item items[],
                                  unsigned int count,
                                  const Location& location);

//
//  printItemsInInventory
//
//  Purpose: To print all the items in the specified array that
//           are in the player inventory.
//  Parameter(s):
//    <1> items: The items to print
//    <2> count: The number of items in the array
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The current description is printed for the
//               Items in items that are in the player
//               inventory.  The items array is assumed to
//               contain count elements.
//
static void printItemsInInventory (const Item items[],
                                   unsigned int count);



int main ()
{
	//static const string GAME_NAME = "blizzard";
	//const unsigned int ITEM_COUNT = 5;

	static const string GAME_NAME = "ghostwood";
	const unsigned int ITEM_COUNT = 9;

	World world(GAME_NAME);
	Location player = world.getStart();

	Item items[ITEM_COUNT];
	//initAllItemsBlizzard(items, ITEM_COUNT);
	initAllItemsGhostwood(items, ITEM_COUNT);

	world.printStartMessage();
	cout << endl;
	world.printDescription(player);
	printItemsAtLocation(items, ITEM_COUNT, player);

	bool is_quit = false;
	while(!is_quit)
	{
		cout << "Next? ";

		string line;
		do  // must get some input!
		{
			getline(cin, line);
		}
		while(line == "");

		char command = line[0];
		switch(command)
		{
		case '#':
			// do nothing
			//cout << "Invalid command!" << endl;
			break;

		case 'q':
			cout << "Are you sure you want to quit? ";
			getline(cin, line);
			if(line != "" && line[0] == 'y')
				is_quit = true;
			break;

		case 'n':
			if(world.canGoNorth(player))
			{
				player = world.getNorth(player);
				world.printDescription(player);
				printItemsAtLocation(items, ITEM_COUNT, player);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;

		case 's':
			if(world.canGoSouth(player))
			{
				player = world.getSouth(player);
				world.printDescription(player);
				printItemsAtLocation(items, ITEM_COUNT, player);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;

		case 'e':
			if(world.canGoEast(player))
			{
				player = world.getEast(player);
				world.printDescription(player);
				printItemsAtLocation(items, ITEM_COUNT, player);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;

		case 'w':
			if(world.canGoWest(player))
			{
				player = world.getWest(player);
				world.printDescription(player);
				printItemsAtLocation(items, ITEM_COUNT, player);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;

		case 't':
			{
				cout << "Take what? ";
				getline(cin, line);

				bool found_it = false;
				if(line != "")
				{
					for(unsigned int i = 0; i < ITEM_COUNT; i++)
					{
						if(items[i].getId() == line[0] &&
						   items[i].isAtLocation(player))
						{
							items[i].moveToInventory();
							found_it = true;
							break;  // stop searching for item
						}
					}
				}
				if(!found_it)
					cout << "Invalid item." << endl;
			}
			break;

		case 'l':
			{
				cout << "Leave what? ";
				getline(cin, line);

				bool found_it = false;
				if(line != "")
				{
					for(unsigned int i = 0; i < ITEM_COUNT; i++)
					{
						if(items[i].getId() == line[0] &&
						   items[i].isInInventory())
						{
							items[i].moveToLocation(player);
							found_it = true;
							break;  // stop searching for item
						}
					}
				}
				if(!found_it)
					cout << "Invalid item." << endl;
			}
			break;

		case 'i':
			printItemsInInventory(items, ITEM_COUNT);
			break;

		default:
			cout << "Invalid command!" << endl;
			break;
		}

		if(world.isDeath(player))
			is_quit = true;
		if(world.isVictory(player))
			is_quit = true;
	}

	int score = 0;
	for(unsigned int i = 0; i < ITEM_COUNT; i++)
	{
		score += items[i].getPlayerPoints();
	}

	cout << endl;
	string points_word = (score == 1) ? "point" : "points";
	cout << "In this game you scored " << score << " " << points_word << "." << endl;
	cout << endl;
	world.printEndMessage();

	if(WAIT_AT_END)
	{
		cout << endl;
		cout << "Press [ENTER] to continue... ";
		string line;
		getline(cin, line);

		// to wait for a non-empty line instead
		//while(line == "")
		//{
		//	getline(cin, line);
		//}
	}

	return 0;
}



void initAllItemsBlizzard (Item items[],
                           unsigned int count)
{
	assert(count == 5);

	items[0] = Item('a', Location(0, 6), 1,
	                "You see Alice (a) trying to read a very small compass.",
	                "Somewhere nearby, you hear Alice (a) jabbering about directions.");
	items[1] = Item('c', Location(0, 6), 1,
	                "You see Charlie (c) lying half-buried in the drifting snow.",
	                "Behind you, Charlie (c) is dragging himself through the snow.");
	items[2] = Item('e', Location(3, 5), 1,
	                "Young Emma (e) is crouched down, out of the wind.",
	                "Young Emma (e) is trying to use you to block the wind.");
	items[3] = Item('d', Location(4, 1), 1,
	                "David (d) is using a stick to write in the snow here.",
	                "David (d) is dashing this way and that, despite the weather.");
	items[4] = Item('b', Location(5, 8), 2,
	                "The twins, Benny and Bobby (b), are huddled together here.",
	                "The twins, Benny and Bobby (b), are huddled behind you.");
}

void initAllItemsGhostwood (Item items[],
                            unsigned int count)
{
	assert(count == 9);

	items[0] = Item('s', Location(0, 3), -5,
	                "There is a black scarab beetle (s) here.",
	                "A black scarab beetle (s) is crawling up your arm.");
	items[1] = Item('c', Location(1, 1), 9,
	                "There is a silver candlestick (c) here.",
	                "You are carrying a silver candlestick (c).");
	items[2] = Item('k', Location(2, 0), 3,
	                "There is an old iron key (k) here.",
	                "You have an old iron key (k) in your pocket.");
	items[3] = Item('t', Location(2, 9), -8,
	                "There is a tarantula (t) here.",
	                "There is a tarantula (t) hanging on your shirt.");
	items[4] = Item('b', Location(3, 4), 4,
	                "There is a book (b) here with an eye drawn on the cover.",
	                "You have a book (b) under your arm with an eye drawn on the cover.");
	items[5] = Item('m', Location(5, 5), -2,
	                "There is a giant moth (m) sleeping here.",
	                "A giant moth (m) is perched on your shoulder.");
	items[6] = Item('p', Location(7, 9), 7,
	                "There is a golden pendant (p) here.",
	                "You are wearing a golden pendant (p).");
	items[7] = Item('d', Location(8, 0), 1,
	                "There is a rune-carved dagger (d) here.",
	                "You have a rune-carved dagger (d) stuck in your belt.");
	items[8] = Item('r', Location(9, 6), 10,
	                "There is a diamond ring (r) here.",
	                "You are wearing a diamond ring (r).");
}

void printItemsAtLocation (const Item items[],
                           unsigned int count,
                           const Location& location)
{
	for(unsigned int i = 0; i < count; i++)
	{
		if(items[i].isAtLocation(location))
			items[i].printDescription();
	}
}

void printItemsInInventory (const Item items[],
                            unsigned int count)
{
	for(unsigned int i = 0; i < count; i++)
	{
		if(items[i].isInInventory())
			items[i].printDescription();
	}
}
