//
//  Location.cpp
//

#include "Location.h"

#include <iostream>
#include <iomanip>

using namespace std;



Location :: Location ()
		: row(0),
		  column(0)
{
}

Location :: Location (int row1, int column1)
		: row   (row1),
		  column(column1)
{
}



bool Location :: operator== (const Location& other) const
{
	return row    == other.row    &&
	       column == other.column;
}



ostream& operator<< (ostream& out,
                     const Location& location)
{
	cout << "(row = "     << setw(1) << right << location.row
	     << ", column = " << setw(1) << right << location.column << ")";
	return out;
}
