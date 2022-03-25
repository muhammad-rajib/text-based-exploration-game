//
//  Game.cpp
//

#include "Game.h"

#include <cassert>
#include <string>

#include "Location.h"
#include "World.h"
#include "Item.h"
#include "ItemManager.h"

using namespace std;



Game :: Game (const string& game_name)
		: world(game_name),
		  item_manager(game_name),
		  player(world.getStart())
{
	assert(isInvariantTrue());
}



bool Game :: isOver () const
{
	assert(isInvariantTrue());

	return world.isDeath(player) ||
	       world.isVictory(player);
}

void Game :: printStartMessage () const
{
	assert(isInvariantTrue());

	world.printStartMessage();
}

void Game :: printEndMessage () const
{
	assert(isInvariantTrue());

	world.printEndMessage();
}

void Game :: printDescription () const
{
	assert(isInvariantTrue());

	world.printDescription(player);
	item_manager.printAtLocation(player);
}

void Game :: printInventory () const
{
	assert(isInvariantTrue());

	item_manager.printInventory();
}

void Game :: printScore () const
{
	assert(isInvariantTrue());

	int score = item_manager.getScore();
	string points_word = (score == 1) ? "point" : "points";
	cout << "In this game you scored " << score << " " << points_word << "." << endl;
	cout << endl;
}



void Game :: reset ()
{
	assert(isInvariantTrue());

	item_manager.reset();
	player = world.getStart();

	assert(isInvariantTrue());
}

void Game :: moveNorth ()
{
	assert(isInvariantTrue());

	if(world.canGoNorth(player))
	{
		player = world.getNorth(player);
		printDescription();
	}
	else
		cout << "There is no way to go in that direction." << endl;

	assert(isInvariantTrue());
}

void Game :: moveSouth ()
{
	assert(isInvariantTrue());

	if(world.canGoSouth(player))
	{
		player = world.getSouth(player);
		printDescription();
	}
	else
		cout << "There is no way to go in that direction." << endl;

	assert(isInvariantTrue());
}

void Game :: moveEast ()
{
	assert(isInvariantTrue());

	if(world.canGoEast(player))
	{
		player = world.getEast(player);
		printDescription();
	}
	else
		cout << "There is no way to go in that direction." << endl;

	assert(isInvariantTrue());
}

void Game :: moveWest ()
{
	assert(isInvariantTrue());

	if(world.canGoWest(player))
	{
		player = world.getWest(player);
		printDescription();
	}
	else
		cout << "There is no way to go in that direction." << endl;

	assert(isInvariantTrue());
}

void Game :: takeItem (char id)
{
	assert(isInvariantTrue());

	item_manager.take(id, player);

	assert(isInvariantTrue());
}

void Game :: leaveItem (char id)
{
	assert(isInvariantTrue());

	item_manager.leave(id, player);

	assert(isInvariantTrue());
}



bool Game :: isInvariantTrue () const
{
	if(!world.isValid(player))
		return false;
	return true;
}

