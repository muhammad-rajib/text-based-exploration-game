#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#include "World.h"

string descriptions[DESCRIPTION_COUNT];


void worldClear(World world)
{
    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            world[i][j] = INACCESSIBLE;
        }
    }
}

void worldLoadAll(World world, string game_name)
{
    worldLoadNodes(world, game_name + "_grid.txt");

    worldLoadDescriptions(world, game_name + "_text.txt");
}

void worldLoadNodes(World world, string filename)
{
    ifstream fp(filename);
    if (!fp)
        cout << "Error, file couldn't be opened" << endl;

    for (int row = 0; row < 6; row++)
    {
        for (int column = 0; column < 9; column++)
        {
            fp >> world[row][column];
            if (!fp)
            {
                cout << "Error reading file for element " << row << "," << column << endl;
            }
        }
    }
}

void worldDebugPrint(const World world)
{
    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            if (j == COLUMN_COUNT - 1)
                cout << world[i][j];
            else
                cout << world[i][j] << "\t";
        }
        cout << endl;
    }
}

bool worldIsValid(const World world, int row, int column)
{
    if ((row < 0) || (row >= ROW_COUNT) || (column < 0) || (column >= COLUMN_COUNT))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool worldCanGoNorth(const World world, int row, int column)
{
    if (row > 0 && world[row - 1][column] != INACCESSIBLE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool worldCanGoSouth(const World world, int row, int column)
{
    if (row < ROW_COUNT - 1 && world[row + 1][column] != INACCESSIBLE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool worldCanGoEast(const World world, int row, int column)
{
    if (column < COLUMN_COUNT - 1 && world[row][column + 1] != INACCESSIBLE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool worldCanGoWest(const World world, int row, int column)
{
    if (column > 0 && world[row][column - 1] != INACCESSIBLE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool worldIsDeath(const World world, int row, int column)
{
    if (world[row][column] == 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool worldIsVictory(const World world, int row, int column)
{
    if (world[row][column] == 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void worldFindValue(const World world, int &row, int &column,
                    NodeValue value_to_find)
{
    row = -1;
    column = -1;

    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            if (world[i][j] == value_to_find)
            {
                row = i;
                column = j;
            }
        }
    }
}

void worldLoadDescriptions(World world, string filename)
{
    string tempDescription;
    ifstream readDescription;

    readDescription.open(filename);

    if (readDescription.fail())
        cout << "cannot open the file " << endl;

    getline(readDescription, tempDescription);

    int line = 0;
    for (int i = 0; i <= DESCRIPTION_COUNT; i++)
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
}

void worldPrintDescription(const World world, int row, int column)
{
    int des_num = world[row][column];
    cout << descriptions[des_num] << endl;
}

void worldPrintStartMessage(const World world)
{
    cout << "Welcome to Blizzard Valley!\n"
            "You and six children were hiking in the mountains when an\n"
            "unexpected blizzard blew up.  Find the children and get them all\n"
            "back to the hiking lodge on the other side of the river.\n"
         << endl;
}

void worldPrintEndMessage(const World world)
{
    cout << "Thank you for playing Blizzard Valley!" << endl;
}
