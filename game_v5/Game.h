//
//  Game.h
//
//  A module to represent the state of the game.
//

#pragma once

#include <string>

#include "Location.h"
#include "World.h"
#include "Item.h"
#include "ItemManager.h"



//
//  Game
//
//  A class to represent the state of the game.
//
//  Class Invariant:
//    <1> world.isValid(player)
//
class Game
{
public:
//
//  Constructor
//
//  Purpose: To create an Game with the specified name.
//  Parameter(s):
//    <1> game_name: The game name
//  Precondition(s):
//    <1> game_name != ""
//  Returns: N/A
//  Side Effect: A new Game is created from the data files for
//               game name game_name.  The player and all the
//               items are placed at their respective starting
//               locations.
//
	Game (const std::string& game_name);

//
//  isOver
//
//  Purpose: To determine if the game is over.  The thame is
//           over when the player reaches the victory node or
//           any death node.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: Whether the game is over.
//  Side Effect: N/A
//
	bool isOver () const;

//
//  printStartMessage
//
//  Purpose: To print the start message for the game.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The game start message is printed.
//  Side Effect: N/A
//
	void printStartMessage () const;

//
//  printEndMessage
//
//  Purpose: To print the end message for the game.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The game end message is printed.
//  Side Effect: N/A
//
	void printEndMessage () const;

//
//  printDescription
//
//  Purpose: To print the current description.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The description for the player's current node is
//           printed.  Then the description for each item at
//           that node is printed.
//  Side Effect: N/A
//
	void printDescription () const;

//
//  printInventory
//
//  Purpose: To print the current player inventory.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The description for each item in the player
//           inventory is printed.
//  Side Effect: N/A
//
	void printInventory () const;

//
//  printScore
//
//  Purpose: To print the player score for the game end.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The player score is printed.  The message is
//               suitable for the game end.
//
	void printScore () const;

//
//  reset
//
//  Purpose: To reset this Game to its initial state.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The player is moved to its starting location.
//               Each item is moved to its starting location.
//
	void reset ();

//
//  moveNorth
//
//  Purpose: To attempt to move the player north.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The player attempts to move north.  This may or
//               may not succeed, and, in either case, a message
//               will be printed.
//
	void moveNorth ();

//
//  moveSouth
//
//  Purpose: To attempt to move the player south.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The player attempts to move south.  This may or
//               may not succeed, and, in either case, a message
//               will be printed.
//
	void moveSouth ();

//
//  moveEast
//
//  Purpose: To attempt to move the player east.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The player attempts to move east.  This may or
//               may not succeed, and, in either case, a message
//               will be printed.
//
	void moveEast ();

//
//  moveWest
//
//  Purpose: To attempt to move the player west.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The player attempts to move west.  This may or
//               may not succeed, and, in either case, a message
//               will be printed.
//
	void moveWest ();

//
//  takeItem
//
//  Purpose: To attempt to take the item with the specified id.
//  Parameter(s):
//    <1> id: The item id
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: If there is an item with id id at the player
//               location, it is moved to the player inventory.
//               Otherwise, a message is printed.
//
	void takeItem (char id);

//
//  leaveItem
//
//  Purpose: To attempt to leave the item with the specified id.
//  Parameter(s):
//    <1> id: The item id
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: If there is an item with id id in the player
//               inventory, it is moved to the player location.
//               Otherwise, a message is printed.
//
	void leaveItem (char id);

private:
//
//  isInvariantTrue
//
//  Purpose: To determine if the class invariant is true.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: Whether the class invariant is true.
//  Side Effect: N/A
//
	bool isInvariantTrue () const;

private:
	World       world;
	ItemManager item_manager;
	Location    player;
};

