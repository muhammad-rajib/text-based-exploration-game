#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

#include "World.h"


// public: constructor
World::World (const string& game_name)
{
    loadNodes(game_name + "_grid.txt");
    loadDescriptions(game_name + "_text.txt");

    assert(isInvariantTrue());
}

// private: member func
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

// private: member func
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

// private: member func
bool World::isInvariantTrue () const
{
    cout << description_count << endl;
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

// public: member func
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
    // descriptions
    for (int des_no = 0; des_no <= description_count; des_no++)
    {
        cout << descriptions[des_no] << endl;
    }
}

// public: member func
bool World::isValid(const Location& location) const
{
    assert(isInvariantTrue());

    if ((location.row < 0) || (location.row >= ROW_COUNT) || (location.column < 0) || (location.column >= COLUMN_COUNT))
        return false;
    else
        return true;
}

// public: member func
bool World::isDeath(const Location& location) const
{
    assert (isInvariantTrue());
    assert (isValid(location));
}

// public: member func
bool World::isVictory(const Location& location) const
{
    assert (isInvariantTrue());
    assert (isValid(location));

    if (nodes[location.row][location.column] == 5)
        return true;
    else
        return false;
}

// public: member func
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

// public: member func
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

// public: member func
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

// public: member func
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

// public: member func
Location World::getNorth (const Location& location) const
{
    assert(isInvariantTrue());
    assert(canGoNorth(location));
}

// public: member func
Location World::getSouth (const Location& location) const
{
    assert(isInvariantTrue());
    assert(canGoSouth(location));
}

// public: member func
Location World::getEast (const Location& location) const
{
    assert(isInvariantTrue());
    assert(canGoEast(location));
}

// public: member func
Location World::getWest (const Location& location) const
{
    assert(isInvariantTrue());
    assert(canGoWest(location));
}

// public: member func
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

// public: member func
void World::printDescription(const Location& location) const
{
    assert(isInvariantTrue());
    assert (isValid(location));
    int des_num = nodes[location.row][location.column];
    cout << descriptions[des_num] << endl;
}

// public: member func
void World::printStartMessage() const
{
    assert(isInvariantTrue());
    cout << "Welcome to Blizzard Valley!\n"
            "You and six children were hiking in the mountains when an\n"
            "unexpected blizzard blew up.  Find the children and get them all\n"
            "back to the hiking lodge on the other side of the river.\n"
         << endl;
}

// public: member func
void World::printEndMessage() const
{
    assert(isInvariantTrue());
    cout << "Thank you for playing Blizzard Valley!" << endl;
}
