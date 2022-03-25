//
//  Location.h
//

#pragma once

#include <iostream>



//
//  Location
//
//  A class to represent a location in the world.  A Location is
//    like a node index, except that it isn't necessarily an
//    integer.  A Location contains sufficient information to
//    uniquely identify a node.
//
//  The Location class is not encapsulated, so the member fields
//    can be accessed using dot notation.  The member field is
//    named node, and represents the node index.
//
class Location
{
public:
//
//  Default Constructor
//
//  Purpose: To create an Location representing a default node.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new Location is created that represents node
//               0.
//
	Location ();

//
//  Initializing Constructor
//
//  Purpose: To create an Location representing the specified
//           node.
//  Parameter(s):
//    <1> node1: The node index
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new Location is created that represents the
//               node with index index.
//
	Location (unsigned int node1);

//
//  Equality Test Operator
//
//  Purpose: To determine if two Locations represent the same
//           node.
//  Parameter(s):
//    <1> other: The other Location
//  Precondition(s): N/A
//  Returns: Whether this Location and other represent the same
//           node in the world.
//  Side Effect: N/A
//
	bool operator== (const Location& other) const;

//
//  isInaccessible
//
//  Purpose: To determine if this Locations represents an
//           inaccessible node.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: Whether this Location is inaccessible.
//  Side Effect: N/A
//
	bool isInaccessible () const;

public:
	unsigned int node;
};

//
//  Stream Insertion Operator
//
//  Purpose: To print the specified Location to the specified
//           output stream.
//  Parameter(s):
//    <1> out: A reference to the output stream
//    <2> location: The Location
//  Precondition(s): N/A
//  Returns: A reference to out.
//  Side Effect: Location location is printed to output stream
//               out.
//
std::ostream& operator<< (std::ostream& out,
                          const Location& location);


