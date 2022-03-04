#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

#include "World.h"


//
// Constructor: World
//
// Purpose: load world nodes and descriptions
// 
//  <1> game_name: hold the file name of world nodes and descriptions files. 
// Side effect: program will be failed for wrong file name. 
//               
World::World (const string& game_name)
{
    loadNodes(game_name + "_grid.txt");
    loadDescriptions(game_name + "_text.txt");
    assert(isInvariantTrue());
}

void World::loadNodes(const string& filename)
{
    ifstream fp(filename);
    if (!fp)
        cout << "Error, file couldn't be opened" << endl;

    for (int r = 0; r < ROW_COUNT; r++)
    {
        for (int c = 0; c < COLUMN_COUNT; c++)
        {
            fp >> nodes[r][c];
            if (!fp)
            {
                cout << "Error reading file for element " << r << "," << c << endl;
            }
        }
    }
}

void World::loadDescriptions(const string& filename)
{
    string tempDescription;
    ifstream readDescription;

    readDescription.open(filename);

    if (readDescription.fail())
        cout << "cannot open the file " << endl;

    getline(readDescription, tempDescription);

    int line = 0;
    for (int i = 0; i <= MAX_DESCRIPTION_COUNT; i++)
    {
        if (i == 0)
        {
            getline(readDescription, tempDescription);
            continue;
        }

        descriptions[line] = "";
        while (readDescription)
        {
            getline(readDescription, tempDescription);
            if (tempDescription.length() == 0)
                break;
            descriptions[line] = descriptions[line] + tempDescription + "\n";
        }
        line++;
    }
    
    size_t count = 0;
    for (size_t i = 0; i < sizeof(descriptions)/sizeof(*descriptions); i++)
        if (descriptions[i] != "")
            description_count++;
}

bool World::isInvariantTrue () const
{
    if (description_count > MAX_DESCRIPTION_COUNT)
        return false;
    
    for (int d=0; d<description_count; d++)
    {
        if (descriptions[d] == "")
            return false;
    }
    
    for (int r=0; r<ROW_COUNT; r++)
    {
        for (int c=0; c<COLUMN_COUNT; c++)
        {
            if (nodes[r][c] > description_count)
                return false;
        }
    }
    return true;
}

void World::debugPrint() const
{
    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            if (j == COLUMN_COUNT - 1)
                cout << nodes[i][j];
            else
                cout << nodes[i][j] << "\t";
        }
        cout << endl;
    }

    cout << description_count << endl;
 
    for (int des_no = 0; des_no <= description_count; des_no++)
    {
        cout << descriptions[des_no] << endl;
    }
}

bool World::isValid(const Location& location) const
{
    assert(isInvariantTrue());

    if ((location.row < 0) || (location.row >= ROW_COUNT) || (location.column < 0) || (location.column >= COLUMN_COUNT))
        return false;
    else
        return true;
}

bool World::isDeath(const Location& location) const
{
    assert (isInvariantTrue());
    if (!isValid(location))
        return false;
    if (nodes[location.row][location.column] == DEATH_NODE)
        return true;
    else
        return false;
}

bool World::isVictory(const Location& location) const
{
    assert (isInvariantTrue());

    if (!isValid(location))
        return false;
    if (nodes[location.row][location.column] == VICTORY_NODE)
        return true;
    else
        return false;
}

bool World::canGoNorth(const Location& location) const
{
    Location loc(location.row-1, location.column);
    if(!isValid(loc))
        return false;
    if (nodes[loc.row][loc.column] == INACCESSIBLE)
        return false;
    else
        return true;
}

bool World::canGoSouth(const Location& location) const
{
    Location loc(location.row+1, location.column);
    if(!isValid(loc))
        return false;
    if (nodes[loc.row][loc.column] == INACCESSIBLE)
        return false;
    else
        return true;
}

bool World::canGoEast(const Location& location) const
{
    Location loc(location.row, location.column+1);
    if(!isValid(loc))
        return false;
    if (nodes[loc.row][loc.column] == INACCESSIBLE)
        return false;
    else
        return true;
}

bool World::canGoWest(const Location& location) const
{
    Location loc(location.row, location.column-1);
    if(!isValid(loc))
        return false;
    if (nodes[loc.row][loc.column] == INACCESSIBLE)
        return false;
    else
        return true;
}

Location World::getNorth (const Location& location) const
{
    assert(isInvariantTrue());
    Location loc(location.row-1, location.column);
    if(canGoNorth(location) == true)
        return loc; 
}

Location World::getSouth (const Location& location) const
{
    assert(isInvariantTrue());
    Location loc(location.row+1, location.column);
    if(canGoSouth(location) == true)
        return loc; 
}

Location World::getEast (const Location& location) const
{
    assert(isInvariantTrue());
    Location loc(location.row, location.column+1);
    if(canGoEast(location) == true)
        return loc; 
}

Location World::getWest (const Location& location) const
{
    assert(isInvariantTrue());
    Location loc(location.row, location.column-1);
    if(canGoWest(location) == true)
        return loc; 
}

Location World::getStart () const
{
    assert(isInvariantTrue());

    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            if (nodes[i][j] == START_NODE)
            {
                return Location(i, j);
            }
        }
    }
    return NO_SUCH_VALUE;
}

void World::printDescription(const Location& location) const
{
    assert(isInvariantTrue());
    assert (isValid(location));
    int des_num = nodes[location.row][location.column];
    cout << descriptions[des_num];
}

void World::printStartMessage() const
{
    assert(isInvariantTrue());
    cout << descriptions[START_MESSAGE] << endl;
}

void World::printEndMessage() const
{
    assert(isInvariantTrue());
    cout << descriptions[END_MESSAGE] << endl;
}
