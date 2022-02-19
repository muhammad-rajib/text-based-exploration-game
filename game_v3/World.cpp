#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

#include "World.h"

string descriptions[MAX_DESCRIPTION_COUNT];


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

    for (int row = 0; row < ROW_COUNT; row++)
    {
        for (int column = 0; column < COLUMN_COUNT; column++)
        {
            fp >> nodes[row][column];
            if (!fp)
            {
                cout << "Error reading file for element " << row << "," << column << endl;
            }
        }
    }
}

bool World::isInvariantTrue () const
{
    if (description_count > MAX_DESCRIPTION_COUNT)
        return false;
    if (descriptions[description_count] == "")
        return false;
    if (nodes[ROW_COUNT][COLUMN_COUNT] > description_count)
        return false;

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
    // descriptions
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
    assert(isInvariantTrue());
    assert (nodes[location.row][location.column] == isValid(location));
}

bool World::isVictory(const Location& location) const
{
    assert(isInvariantTrue());

    if (nodes[location.row][location.column] == 5)
        return true;
    else
        return false;
}

bool World::canGoNorth(const Location& location) const
{
    assert(isInvariantTrue());
    assert ((location.row > 0 && nodes[location.row - 1][location.column]) != INACCESSIBLE);
}

bool World::canGoSouth(const Location& location) const
{
    assert(isInvariantTrue());
    assert (location.row < ROW_COUNT - 1 && nodes[location.row + 1][location.column] != INACCESSIBLE);
}

bool World::canGoEast(const Location& location) const
{
    assert(isInvariantTrue());
    assert (location.column < COLUMN_COUNT - 1 && nodes[location.row][location.column + 1] != INACCESSIBLE);
}

bool World::canGoWest(const Location& location) const
{
    assert(isInvariantTrue());
    assert (location.column > 0 && nodes[location.row][location.column - 1] != INACCESSIBLE);
}

Location World::getNorth (const Location& location) const
{
    assert(isInvariantTrue());
    assert(isInvariantTrue());
    assert(isValid(location));
    assert(canGoNorth(location));
    int north_location = nodes[location.row][location.column];
}

Location World::getSouth (const Location& location) const
{
    assert(isInvariantTrue());
    assert(isInvariantTrue());
    assert(isValid(location));
    assert(canGoSouth(location));
    int north_location = nodes[location.row][location.column]; 
}

Location World::getEast (const Location& location) const
{
    assert(isInvariantTrue());
    assert(isInvariantTrue());
    assert(isValid(location));
    assert(canGoEast(location));
    int north_location = nodes[location.row][location.column];
}

Location World::getWest (const Location& location) const
{
    assert(isInvariantTrue());
    assert(isInvariantTrue());
    assert(isValid(location));
    assert(canGoWest(location));
    int north_location = nodes[location.row][location.column];
}

Location World::getStart () const
{
    assert(isInvariantTrue());
    int row = -1;
    int column = -1;

    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            if (nodes[i][j] == START_NODE)
            {
                row = i;
                column = j;
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
        description_count = description_count + 1;
    }
}

void World::printDescription(const Location& location) const
{
    assert(isInvariantTrue());
    assert (isValid(location));
    int des_num = nodes[location.row][location.column];
    cout << descriptions[des_num] << endl;
}

void World::printStartMessage() const
{
    assert(isInvariantTrue());
    cout << "Welcome to Blizzard Valley!\n"
            "You and six children were hiking in the mountains when an\n"
            "unexpected blizzard blew up.  Find the children and get them all\n"
            "back to the hiking lodge on the other side of the river.\n"
         << endl;
}

void World::printEndMessage() const
{
    assert(isInvariantTrue());
    cout << "Thank you for playing Blizzard Valley!" << endl;
}
