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
#include "Node.h"

using namespace std;




World :: World (const string& game_name)
{
	loadNodes       (game_name + "_nodes.txt");
	loadDescriptions(game_name + "_text.txt");

	assert(isInvariantTrue());
}



void World :: debugPrint () const
{
	cout << "Nodes (" << node_count << "):" << endl;
	cout << "-----------" << endl;
	cout << node_count << endl;
	cout << start_node << "\t" << victory_node << "\t" << start_message << "\t" << end_message << endl;
	for(unsigned int n = 0; n < node_count; n++)
	{
		nodes[n].debugPrint();
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
	assert(isInvariantTrue());

	return location.node < node_count;
}

bool World :: isDeath (const Location& location) const
{
	assert(isInvariantTrue());
	assert(isValid(location));

	return nodes[location.node].isDeath();
}

bool World :: isVictory (const Location& location) const
{
	assert(isInvariantTrue());
	assert(isValid(location));

	return location.node == victory_node;
}

bool World :: canGoNorth (const Location& location) const
{
	assert(isInvariantTrue());
	assert(isValid(location));

	if(nodes[location.node].getNorth().isInaccessible())
		return false;
	return true;
}

bool World :: canGoSouth (const Location& location) const
{
	assert(isInvariantTrue());
	assert(isValid(location));

	if(nodes[location.node].getSouth().isInaccessible())
		return false;
	return true;
}

bool World :: canGoEast (const Location& location) const
{
	assert(isInvariantTrue());
	assert(isValid(location));

	if(nodes[location.node].getEast().isInaccessible())
		return false;
	return true;
}

bool World :: canGoWest (const Location& location) const
{
	assert(isInvariantTrue());
	assert(isValid(location));

	if(nodes[location.node].getWest().isInaccessible())
		return false;
	return true;
}

Location World :: getNorth (const Location& location) const
{
	assert(isInvariantTrue());
	assert(isValid(location));
	assert(canGoNorth(location));

	return Location(nodes[location.node].getNorth());
}

Location World :: getSouth (const Location& location) const
{
	assert(isInvariantTrue());
	assert(isValid(location));
	assert(canGoSouth(location));

	return Location(nodes[location.node].getSouth());
}

Location World :: getEast (const Location& location) const
{
	assert(isInvariantTrue());
	assert(isValid(location));
	assert(canGoEast(location));

	return Location(nodes[location.node].getEast());
}

Location World :: getWest (const Location& location) const
{
	assert(isInvariantTrue());
	assert(isValid(location));
	assert(canGoWest(location));

	return Location(nodes[location.node].getWest());
}

Location World :: getStart () const
{
	assert(isInvariantTrue());

	return start_node;
}

void World :: printStartMessage () const
{
	assert(isInvariantTrue());

	assert(start_message < MAX_DESCRIPTION_COUNT);
	assert(start_message < description_count);
	cout << descriptions[start_message];
}

void World :: printEndMessage () const
{
	assert(isInvariantTrue());

	assert(end_message < MAX_DESCRIPTION_COUNT);
	assert(end_message < description_count);
	cout << descriptions[end_message];
}

void World :: printDescription (const Location& location) const
{
	assert(isInvariantTrue());
	assert(isValid(location));

	unsigned int index = nodes[location.node].getDescription();
	assert(index < MAX_DESCRIPTION_COUNT);
	assert(index < description_count);
	cout << descriptions[index];
}



void World :: loadNodes (const string& filename)
{
	assert(filename != "");

	ifstream fin(filename.c_str());
	if(!fin)
	{
		cout << "Error: Could not open file \"" << filename << "\"" << endl;
		exit(EXIT_FAILURE);  // end program immediately
	}

	// read first line (number of nodes)
	fin >> node_count;

	// read second line (start and victory node indexes, start and end messages)
	fin >> start_node;
	fin >> victory_node;
	fin >> start_message;
	fin >> end_message;

	// discard anything else on start/victory line
	string end_of_start_line;
	getline(fin, end_of_start_line);

	// read nodes, one line at a time
	for(unsigned int n = 0; n < node_count; n++)
	{
		// read node type
		char node_type;
		fin >> node_type;

		// read description
		unsigned int description;
		fin >> description;

		// read links (node index in each direction)
		unsigned int north;
		unsigned int south;
		unsigned int east;
		unsigned int west;
		fin >> north;
		fin >> south;
		fin >> east;
		fin >> west;

		// construct Node object for array
		if(node_type == 'N')
			nodes[n] = Node(description, north, south, east, west, false);
		else if(node_type == 'D')
			nodes[n] = Node(description, north, south, east, west, true);
		else if(node_type == 'O')
		{
			// these will be ObstructedNodes in Assignment 6
			nodes[n] = Node(description, north, south, east, west, false);
		}

		// discard anything else on the line
		string end_of_node_line;
		getline(fin, end_of_node_line);
	}

	// fails if no blank line at the end
	//if(!fin)
	//{
	//	cout << "Error: While reading file \"" << filename << "\"" << endl;
	//	exit(EXIT_FAILURE);  // end program immediately
	//}
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

	// fails if no blank line at the end
	//if(!fin)
	//{
	//	cout << "Error: While reading file \"" << filename << "\"" << endl;
	//	exit(EXIT_FAILURE);  // end program immediately
	//}
}

bool World :: isInvariantTrue () const
{
	if(node_count > MAX_NODE_COUNT)
		return false;
	if(start_node >= node_count)
		return false;
	if(victory_node >= node_count)
		return false;
	if(description_count > MAX_DESCRIPTION_COUNT)
		return false;
	if(start_message >= description_count)
		return false;
	if(end_message >= description_count)
		return false;

	for(unsigned int n = 0; n < node_count; n++)
	{
		if(nodes[n].getDescription() >= description_count)
			return false;
	}

	for(unsigned int d = 0; d < description_count; d++)
	{
		if(descriptions[d] == "")
			return false;
	}

	return true;
}
