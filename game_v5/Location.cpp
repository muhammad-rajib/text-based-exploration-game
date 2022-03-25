//
//  Location.cpp
//

#include "Location.h"

#include <iostream>

using namespace std;

static const unsigned int INACCESSIBLE = 0;



Location :: Location ()
		: node(INACCESSIBLE)
{
}

Location :: Location (unsigned int node1)
		: node(node1)
{
}



bool Location :: operator== (const Location& other) const
{
	return node == other.node;
}

bool Location :: isInaccessible () const
{
	return node == INACCESSIBLE;
}



ostream& operator<< (ostream& out,
                     const Location& location)
{
	if(location.node == INACCESSIBLE)
		cout << "(node = INACCESSIBLE)";
	else
		cout << "(node = " << location.node << ")";
	return out;
}
