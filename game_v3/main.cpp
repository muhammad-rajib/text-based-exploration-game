#include <string>
#include <iostream>
using namespace std;

#include "World.h"
#include "Item.h"

const int ITEM_COUNT = 5;
Item Items[ITEM_COUNT] = {
    {
       'a', 0, 6, 0, 6, false, 1,
        "You see Alice (a) here, trying to read a very small compass.",
        "Somewhere nearby, you hear Alice (a) jabbering about directions."
    },
    {
        'b', 5, 8, 5, 8, false, 2,
        "The twins, Benny and Bobby (b), are huddled together here.",
        "The twins, Benny and Bobby (b), are huddled behind you."
    },
    {
        'c', 0, 6, 0, 6, false, 1,
        "You see Charlie (c) lying half-buried in the drifting snow here.",
        "Behind you, Charlie (c) is dragging himself through the snow."
    },
    {
        'd', 4, 1, 4, 1, false, 1,
        "David (d) is using a stick to write in the snow here.",
        "David (d) is dashing this way and that, despite the weather."
    },
    {
        'e', 3, 5, 3, 5, false, 1,
        "Young Emma (e) is crouched down here, out of the wind.",
        "Young Emma (e) is trying to use you to block the wind."
    }
};


// helper function: to find every item at a location
// and print their descriptions
void printItemDescription (int row, int column) {
    for (const auto &arr : Items) {
        if (itemIsAtLocation(arr, row, column))
            itemPrintDescription(arr);
    }
}


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

    // total points
    int total_points = 0;

    // game start message
    worldPrintStartMessage(world);

    // description for player current possition
    worldPrintDescription(world, row, column);
    printItemDescription(row, column);
    
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

        if (input_str[0] == quit)
        {
            cout << "Are you sure you want to quit? ";
            getline(cin, quit_msg);
            
            if (quit_msg[0] == quit_confirm)
                break;
            else
                continue;
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
                printItemDescription(row, column);
            }
            else
                cout << "There is no way to go in that direction" << endl;
        }
        else if (input_str[0] == south) // south movement
        {
            move_south = worldCanGoSouth(world, row, column);
            if (move_south == true)
            {
                row++;
                worldPrintDescription(world, row, column);
                printItemDescription(row, column);
            }
            else
                cout << "There is no way to go in that direction" << endl;
        }
        else if (input_str[0] == east) // east movement
        {
            move_east = worldCanGoEast(world, row, column);
            if (move_east == true)
            {
                column++;
                worldPrintDescription(world, row, column);
                printItemDescription(row, column);
            }
            else
                cout << "There is no way to go in that direction" << endl;
        }
        else if (input_str[0] == west) // west movement
        {
            move_west = worldCanGoWest(world, row, column);
            if (move_west == true)
            {
                column--;
                worldPrintDescription(world, row, column);
                printItemDescription(row, column);
            }
            else
                cout << "There is no way to go in that direction" << endl;
        }
        else if (input_str[0] == 't') // take command
        {
            string player_input;
            cout << "Take what? ";
            getline(cin, player_input);

            // empty input
            if (player_input == "")
            {
                cout << "Invalid item" << endl;
                continue;
            }
            
            if (player_input[0] == 'a')
            {
                if (itemIsInInventory(Items[0]) != true && 
                    itemIsAtLocation(Items[0], row, column) == true)
                {
                    itemMoveToInventory(Items[0]);
                    total_points = total_points + itemGetPlayerPoints(Items[0]);
                }
            }
            else if (player_input[0] == 'b')
            {
                if (itemIsInInventory(Items[1]) != true && 
                    itemIsAtLocation(Items[1], row, column) == true)
                {
                    itemMoveToInventory(Items[1]);
                    total_points = total_points + itemGetPlayerPoints(Items[1]);
                }
            }
            else if (player_input[0] == 'c')
            {
                if (itemIsInInventory(Items[2]) != true && 
                    itemIsAtLocation(Items[2], row, column) == true)
                {
                    itemMoveToInventory(Items[2]);
                    total_points = total_points + itemGetPlayerPoints(Items[2]);
                }
            }
            else if (player_input[0] == 'd')
            {
                if (itemIsInInventory(Items[3]) != true && 
                    itemIsAtLocation(Items[3], row, column) == true)
                {
                    itemMoveToInventory(Items[3]);
                    total_points = total_points + itemGetPlayerPoints(Items[3]);
                }
            }
            else if (player_input[0] == 'e')
            {
                if (itemIsInInventory(Items[4]) != true && 
                    itemIsAtLocation(Items[4], row, column) == true)
                {
                    itemMoveToInventory(Items[4]);
                    total_points = total_points + itemGetPlayerPoints(Items[4]);
                }
            }
            else
                cout << "Invalid item" << endl;
        }
        else if (input_str[0] == 'l') // leave command
        {
            string player_input;
            cout << "Leave what? ";
            getline(cin, player_input);

            // empty input
            if (player_input == "")
            {
                cout << "Invalid item" << endl;
                continue;
            }
            
            if (player_input[0] == 'a')
            {
                if (itemIsInInventory(Items[0]) == true)
                {
                    total_points = total_points - itemGetPlayerPoints(Items[0]);
                    itemMoveToLocation(Items[0], row, column);
                    //itemReset(Items[0]);
                }
            }
            else if (player_input[0] == 'b')
            {
                if (itemIsInInventory(Items[1]) == true)
                {
                    total_points = total_points - itemGetPlayerPoints(Items[1]);
                    itemMoveToLocation(Items[1], row, column);
                    //itemReset(Items[1]);
                }
            }
            else if (player_input[0] == 'c')
            {
                if (itemIsInInventory(Items[2]) == true)
                {
                    total_points = total_points - itemGetPlayerPoints(Items[2]);
                    itemMoveToLocation(Items[2], row, column);
                    //itemReset(Items[2]);
                }
            }
            else if (player_input[0] == 'd')
            {
                if (itemIsInInventory(Items[3]) == true)
                {
                    total_points = total_points - itemGetPlayerPoints(Items[3]);
                    itemMoveToLocation(Items[3], row, column);
                    //itemReset(Items[3]);
                }
            }
            else if (player_input[0] == 'e')
            {
                if (itemIsInInventory(Items[4]) == true)
                {
                    total_points = total_points - itemGetPlayerPoints(Items[4]);
                    itemMoveToLocation(Items[4], row, column);
                    //itemReset(Items[4]);
                }
            }
            else
                cout << "Invalid item" << endl;
        }
        else if (input_str[0] == 'i') // display the inventory
        {
            for (const auto &arr : Items)
            {
                if (itemIsInInventory(arr) == true)
                    cout << arr.inventory_description << endl;
            }
        }
        else
        {
            cout << "Invalid command!" << endl;
            continue;
        }
        
        // check wether the player is at a death node
        is_death_node = worldIsDeath(world, row, column);
        if (is_death_node == true) break;

        // check wether the player is at a victory node
        is_victory_node = worldIsVictory(world, row, column);
        if (is_victory_node == true) break;
    }

    // game end message
    cout << endl;
    worldPrintEndMessage(world);
    cout << "In this game you scored " << total_points << " points." << endl;
}
