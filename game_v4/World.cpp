//
//  World.cpp
//

#include "World.h"

#include <cassert>
#include <cstdlib>  // for exit()
#include <string>
#include <iostream>
#include <fstream>

#include "Location.h"

using namespace std;



World :: World (const string& game_name)
{
	loadNodes       (game_name + "_grid.txt");
	loadDescriptions(game_name + "_text.txt");

	assert(invariant());
}



void World :: debugPrint () const
{
	cout << "Nodes (" << ROW_COUNT << " x " << COLUMN_COUNT << "):" << endl;
	cout << "----------------" << endl;
	for(unsigned int r = 0; r < ROW_COUNT; r++)
	{
		for(unsigned int c = 0; c < COLUMN_COUNT; c++)
		{
			cout << nodes[r][c];
			if(c + 1 < COLUMN_COUNT)
				cout << "\t";
			else
				cout << endl;
		}
	}
	cout << endl;

	cout << "Descriptions (" << description_count << "):" << endl;
	cout << "------------------" << endl;
	for(unsigned int d = 0; d < description_count; d++)
	{
		cout << descriptions[d] << endl;
	}
}

bool World :: isValid (const Location& location) const
{
	assert(invariant());

	if(location.row    <  0)
		return false;
	if(location.column <  0)
		return false;
	if(location.row    >= ROW_COUNT)
		return false;
	if(location.column >= COLUMN_COUNT)
		return false;
	return true;
}

bool World :: isDeath (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	if(nodes[location.row][location.column] == DEATH_NODE)
		return true;
	else
		return false;
}

bool World :: isVictory (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	if(nodes[location.row][location.column] == VICTORY_NODE)
		return true;
	else
		return false;
}

bool World :: canGoNorth (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	Location north = location;
	north.row--;

	if(!isValid(north))
		return false;
	if(nodes[north.row][north.column] == INACCESSIBLE)
		return false;
	return true;
}

bool World :: canGoSouth (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	Location south = location;
	south.row++;

	if(!isValid(south))
		return false;
	if(nodes[south.row][south.column] == INACCESSIBLE)
		return false;
	return true;
}

bool World :: canGoEast (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	Location east = location;
	east.column++;

	if(!isValid(east))
		return false;
	if(nodes[east.row][east.column] == INACCESSIBLE)
		return false;
	return true;
}

bool World :: canGoWest (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	Location west = location;
	west.column--;

	if(!isValid(west))
		return false;
	if(nodes[west.row][west.column] == INACCESSIBLE)
		return false;
	return true;
}

Location World :: getNorth (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));
	assert(canGoNorth(location));

	Location north = location;
	north.row--;
	assert(isValid(north));

	return north;
}

Location World :: getSouth (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));
	assert(canGoSouth(location));

	Location south = location;
	south.row++;
	assert(isValid(south));

	return south;
}

Location World :: getEast (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));
	assert(canGoEast(location));

	Location east = location;
	east.column++;
	assert(isValid(east));

	return east;
}

Location World :: getWest (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));
	assert(canGoWest(location));

	Location west = location;
	west.column--;
	assert(isValid(west));

	return west;
}

Location World :: getStart () const
{
	assert(invariant());

	for(unsigned int r = 0; r < ROW_COUNT; r++)
	{
		for(unsigned int c = 0; c < COLUMN_COUNT; c++)
		{
			if(nodes[r][c] == START_NODE)
				return Location(r, c);
		}
	}

	return NO_SUCH_VALUE;
}

void World :: printStartMessage () const
{
	assert(invariant());

	assert(START_MESSAGE < MAX_DESCRIPTION_COUNT);
	assert(START_MESSAGE < description_count);
	cout << descriptions[START_MESSAGE];
}

void World :: printEndMessage () const
{
	assert(invariant());

	assert(END_MESSAGE < MAX_DESCRIPTION_COUNT);
	assert(END_MESSAGE < description_count);
	cout << descriptions[END_MESSAGE];
}

void World :: printDescription (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	unsigned int index = nodes[location.row][location.column];
	assert(index < MAX_DESCRIPTION_COUNT);
	assert(index < description_count);
	cout << descriptions[index];
}



void World :: loadNodes (const string& filename)
{
	assert(filename != "");

	ifstream fin;
	fin.open(filename.c_str());
	if(!fin.good())
	{
		cout << "Error: Could not open file \"" << filename << "\"" << endl;
		exit(EXIT_FAILURE);  // end program immediately
	}

	for(unsigned int r = 0; r < ROW_COUNT; r++)
	{
		for(unsigned int c = 0; c < COLUMN_COUNT; c++)
		{
			fin >> nodes[r][c];
		}
	}

	if(!fin)
	{
		cout << "Error: While reading file \"" << filename << "\"" << endl;
		exit(EXIT_FAILURE);  // end program immediately
	}
}

void World :: loadDescriptions (const string& filename)
{
	assert(filename != "");

	ifstream fin;
	fin.open(filename.c_str());
	if(!fin.good())
	{
		cout << "Error: Could not open file \"" << filename << "\"" << endl;
		exit(EXIT_FAILURE);  // end program immediately
	}

	// read description count, discard anything else on line
	fin >> description_count;
	string line;
	getline(fin, line);

	// read blank line
	getline(fin, line);

	// read descriptions
	for(unsigned int d = 0; d < description_count; d++)
	{
		descriptions[d] = "";

		getline(fin, line);
		while(line != "" && fin.good())
		{
			descriptions[d] += line + "\n";
			getline(fin, line);
		}
	}

	if(!fin)
	{
		cout << "Error: While reading file \"" << filename << "\"" << endl;
		exit(EXIT_FAILURE);  // end program immediately
	}
}

bool World :: invariant () const
{
	if(description_count > MAX_DESCRIPTION_COUNT)
		return false;

	for(unsigned int r = 0; r < ROW_COUNT; r++)
	{
		for(unsigned int c = 0; c < COLUMN_COUNT; c++)
		{
			if(nodes[r][c] >= description_count)
				return false;
		}
	}

	for(unsigned int d = 0; d < description_count; d++)
	{
		if(descriptions[d] == "")
			return false;
	}

	return true;
}
