//
//  Node.h
//
//  A module to represent a single node in the world.
//

#pragma once

#include "Location.h"



//
//  Node
//
//  A class to represent a single node in the world.
//
class Node
{
public:
//
//  Default Constructor
//
//  Purpose: To create a Node with no links.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new Node is created with description index
//               0, and with node 0 in all firections.  This
//               node is not a death node.
//
	Node ();

//
//  Initializing Constructor
//
//  Purpose: To create a Node with the specified values.
//  Parameter(s):
//    <1> description1: The description index
//    <2> north1: The node to the north
//    <3> south1: The node to the south
//    <4> east1: The node to the east
//    <5> west1: The node to the west
//    <6> is_death1: Whether this is a death node
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new Node is created with description index
//               index.  To the north is node north1, to the
//               south is south1, to the east is east1, and to
//               the west is west1.  If is_death1 == true, this
//               is a death node.  Otherwise, it is not.
//
	Node (unsigned int description1,
	      unsigned int north1,
	      unsigned int south1,
	      unsigned int east1,
	      unsigned int west1,
	      bool is_death1);

//
//  debugPrint
//
//  Purpose: To print the complete state of this Node.  This
//           function is intended for use when debugging.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: This Node is printed to standard output (cout).
//               This includes the value of all member
//               variables.
//
	void debugPrint () const;

//
//  getDescription
//
//  Purpose: To determine the description index.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The description index for this Node.
//  Side Effect: N/A
//
	unsigned int getDescription () const;

//
//  getNorth
//
//  Purpose: To determine the location to the north.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The Location to the north of this Node.
//  Side Effect: N/A
//
	Location getNorth () const;

//
//  getSouth
//
//  Purpose: To determine the location to the south.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The Location to the south of this Node.
//  Side Effect: N/A
//
	Location getSouth () const;

//
//  getEast
//
//  Purpose: To determine the location to the east.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The Location to the east of this Node.
//  Side Effect: N/A
//
	Location getEast  () const;

//
//  getWest
//
//  Purpose: To determine the location to the west.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The Location to the west of this Node.
//  Side Effect: N/A
//
	Location getWest  () const;

//
//  isDeath
//
//  Purpose: To determine whether this is a death node.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: Whether this Node is a death node.
//  Side Effect: N/A
//
	bool isDeath () const;

private:
	unsigned int description;
	unsigned int north;
	unsigned int south;
	unsigned int east;
	unsigned int west;
	bool is_death;
};

