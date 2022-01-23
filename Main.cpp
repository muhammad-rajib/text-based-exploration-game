#include <string>
#include <iostream>

using namespace std;

#include "World.h"
#include "World.cpp"


int main()
{
    // variable initializations
    string input_str;
    string quit_msg;

    bool is_death_node;
    bool is_victory_node;

    char quit = 'q';
    char quit_confirm = 'y';
    char north = 'n';
    char south = 's';
    char east = 'e';
    char west = 'w';
    char comment = '#';

    // load the world
    World world;
    worldLoadAll(world, "blizzard");

    // start node
    int row = 4;
    int column = 1;

    // game start message
    worldPrintStartMessage(world);

    // description for player current possition
    worldPrintDescription(world, row, column);
    
    // Main Loop
    while (true)
    {
        cout << "Next? ";

        // movement initialization
        bool move_north = false;
        bool move_south = false;
        bool move_west = false;
        bool move_east = false;

        // Player input
        getline(cin, input_str);

        // game quit condition checking
        if (input_str[0] == quit)
        {
            cout << "Are you sure you want to quit? ";
            getline(cin, quit_msg);
            if (quit_msg[0] == quit_confirm)
                break;
            else
            {
                continue;
            }
        }

        // ignore comments
        if (input_str[0] == comment)
            continue;

        // empty input
        if (input_str == "")
        {
            cout << "Invalid command!" << endl;
            continue;
        }

        if (input_str[0] == north) // north movement
        {
            move_north = worldCanGoNorth(world, row, column);
            if (move_north == true)
            {
                row--;
                worldPrintDescription(world, row, column);
            }
            else
            {
                cout << "There is no way to go in that direction" << endl;
            }
        }
        else if (input_str[0] == south) // south movement
        {
            move_south = worldCanGoSouth(world, row, column);
            if (move_south == true)
            {
                row++;
                worldPrintDescription(world, row, column);
            }
            else
            {
                cout << "There is no way to go in that direction" << endl;
            }
        }
        else if (input_str[0] == east) // east movement
        {
            move_east = worldCanGoEast(world, row, column);
            if (move_east == true)
            {
                column++;
                worldPrintDescription(world, row, column);
            }
            else
            {
                cout << "There is no way to go in that direction" << endl;
            }
        }
        else if (input_str[0] == west) // west movement
        {
            move_west = worldCanGoWest(world, row, column);
            if (move_west == true)
            {
                column--;
                worldPrintDescription(world, row, column);
            }
            else
            {
                cout << "There is no way to go in that direction" << endl;
            }
        }
        else
        {
            cout << "Invalid command!" << endl;
            continue;
        }
        
        // check wether the player is at a death node
        is_death_node = worldIsDeath(world, row, column);
        if (is_death_node == true)
        {
            break;
        }

        // check wether the player is at a victory node
        is_victory_node = worldIsVictory(world, row, column);
        if (is_victory_node == true)
        {
            break;
        }
    }
    
    // game end message
    cout << endl;
    worldPrintEndMessage(world);
}
