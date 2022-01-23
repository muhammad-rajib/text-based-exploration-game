#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#include "World.h"

string descriptions[DESCRIPTION_COUNT];

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

void worldLoadDescriptions(World world, string filename)
{
    string tempDescription;
    ifstream readDescription;

    readDescription.open("blizzard_text.txt");

    if (readDescription.fail())
        cout << "cannot open the file " << endl;

    getline(readDescription, tempDescription);

    int line = 0;
    for (int i = 0; i <= DESCRIPTION_COUNT; i++)
    {
        if (i == 0) // skip first line value 26
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

    for (int i=0; i<26; i++)
        cout << i << "-->" << descriptions[i] << endl;
}

void worldPrintDescription(const World world,
                           int row, int column)
{
    int des_num = world[row][column];
    cout << descriptions[des_num] << endl;
}

int main()
{
    World world;
    worldLoadNodes(world, "blizzard_grid.txt");
    
    worldLoadDescriptions(world, "blizzard_text.txt");
    
    worldPrintDescription(world, 1, 2);
    return 0;
}