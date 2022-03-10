//
//  Item.h
//
//  A module to represent a single item in the game.
//

#pragma once

#include <string>

#include "Location.h"



//
//  ID_NOT_INITIALIZED
//
//  A special ID value indicating that an Item has not been
//    initialized.
//
const char ID_NOT_INITIALIZED = '\0';



//
//  Item
//
//  A record to represent an item.
//
//  Class Invariant:
//    <1>     world_description != ""
//    <2> inventory_description != ""
//
class Item 
{
public:
//
//  Default Constructor
//
//  Purpose: To create an Item with default values.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new Item is created with an id of
//               ID_NOT_INITIALIZED, with starting and current
//               locations of (0, 0), with a points value of 0,
//               and with error messages for descriptions.
//
	Item ();

//
//  Inititalizing Constructor
//
//  Purpose: To create an Item with the specified values.
//  Parameter(s):
//    <1> id1: The id for the item
//    <2> start1: The starting location
//    <3> points1: How many points the item is worth
//    <4> world_description1: The description of the item when
//                            it is at a location in the world
//    <5> inventory_description1: The description of the item
//                                when it is in the player
//                                inventory
//  Precondition(s):
//    <1> id1 != ID_NOT_INITIALIZED
//    <2> world_description1 != ""
//    <3> inventory_description1 != ""
//  Returns: N/A
//  Side Effect: A new Item is created with id id1, with
//               starting and current locations of start1, with
//               a points value of points1, and with world and
//               inventory descriptions of world_description1 and
//               inventory_description1.
//
	Item (char id1,
	      const Location& location,
	      int points1,
	      const std::string& world_description1,
	      const std::string& inventory_description1);

//
//  debugPrint
//
//  Purpose: To display the state of this Item.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The values for this Item are printed.
//
	void debugPrint () const;

//
//  isInitialized
//
//  Purpose: To determine whether this Item has been
//           initialized.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: Whether this Item has been initialized.
//  Side Effect: N/A
//
	bool isInitialized () const;

//
//  getId
//
//  Purpose: To determine the id of this Item.
//  Parameter(s): N/A
//  Precondition(s):
//    <1> isInitialized()
//  Returns: The id of this Item.
//  Side Effect: N/A
//
	char getId () const;

//
//  isInInventory
//
//  Purpose: To determine whether this Item is in the player
//           inventory.
//  Parameter(s): N/A
//  Precondition(s):
//    <1> isInitialized()
//  Returns: Whether this Item is in the player inventory.
//  Side Effect: N/A
//
	bool isInInventory () const;

//
//  isAtLocation
//
//  Purpose: To determine whether this Item is at the specified
//           location.
//  Parameter(s):
//    <1> location: The location to check
//  Precondition(s):
//    <1> isInitialized()
//  Returns: Whether this Item is in at location location.
//  Side Effect: N/A
//
	bool isAtLocation (const Location& location) const;

//
//  getPlayerPoints
//
//  Purpose: To determine how many points this Item is currently
//           worth to the player.
//  Parameter(s): N/A
//  Precondition(s):
//    <1> isInitialized()
//  Returns: How many points this Item is worth to the player at
//           present.
//  Side Effect: N/A
//
	int getPlayerPoints () const;

//
//  printDescription
//
//  Purpose: To print the current description for this Item.
//  Parameter(s): N/A
//  Precondition(s):
//    <1> isInitialized()
//  Returns: N/A
//  Side Effect: The current description for this Item is
//               printed.
//
	void printDescription () const;

//
//  Less Than Operator
//
//  Purpose: To determine whether this Item should be sorted
//           before the specified Item.
//  Parameter(s):
//    <1> other: The Item to compare to
//  Precondition(s):
//    <1> isInitialized()
//    <2> other.isInitialized()
//  Returns: Whether this Item should be before Item item.
//  Side Effect: N/A
//
	bool operator< (const Item& other) const;

//
//  reset
//
//  Purpose: To reset this Item.
//  Parameter(s): N/A
//  Precondition(s):
//    <1> isInitialized()
//  Returns: N/A
//  Side Effect: This Item is moved to its starting location.
//
	void reset ();

//
//  moveToInventory
//
//  Purpose: To move this Item to the player inventory.
//  Parameter(s): N/A
//  Precondition(s):
//    <1> isInitialized()
//  Returns: N/A
//  Side Effect: This Item is moved to the player inventory.
//
	void moveToInventory ();

//
//  moveToLocation
//
//  Purpose: To move this Item to the specified location.
//  Parameter(s):
//    <1> location: The new Location
//  Precondition(s):
//    <1> isInitialized()
//  Returns: N/A
//  Side Effect: This Item is moved to location location.
//
	void moveToLocation (const Location& location);

private:
//
//  invariant
//
//  Purpose: To determine if the class invariant is true.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: Whether the class invarint is true.
//  Side Effect: N/A
//
	bool invariant () const;

private:
	char id;
	Location start;
	Location current;
	bool is_in_inventory;
	int points;
	std::string world_description;
	std::string inventory_description;
};



//
//  Less Than Operator (non-member)
//
//  Purpose: To determine whether one Item should be sorted
//           before another Item.
//  Parameter(s):
//    <1> lhs: The left-hand-side Item
//    <2> rhs: The right-hand-side Item
//  Precondition(s):
//    <1> lhs.isInitialized()
//    <2> rhs.isInitialized()
//  Returns: Whether Item lhs should be before Item rhs.
//  Side Effect: N/A
//
//bool operator< (const Item& lhs, const Item& rhs);

