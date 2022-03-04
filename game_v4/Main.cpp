#include <string>
#include <iostream>
using namespace std;

#include "World.h"
#include "Item.h"

const int ITEM_COUNT = 9;
Item items[ITEM_COUNT] = {
    {
        's', Location(0, 3), -5,
        "There is a black scarab beetle (s) here.",
        "A black scarab beetle (s) is crawling up your arm."
    },
    {
        'c', Location(1, 1), 9,
        "There is a silver candlestick (c) here.",
        "You are carrying a silver candlestick (c)."
    },
    {
        'k', Location(2, 0), 3,
        "There is an old iron key (k) here.",
        "You have an old iron key (k) in your pocket."
    },
    {
        't', Location(2, 9), -8,
        "There is a tarantula (t) here.",
        "There is a tarantula (t) hanging on your shirt."
    },
    {
        'b', Location(3, 4), 4,
        "There is a book (b) here with an eye drawn on the cover.",
        "You have a book (b) under your arm with an eye drawn on the cover."
    },
    {
        'm', Location(5, 5), -2,
        "There is a giant moth (m) sleeping here.",
        "A giant moth (m) is perched on your shoulder."
    },
    {
        'p', Location(7, 9), 7,
        "There is a golden pendant (p) here.",
        "You are wearing a golden pendant (p)."
    },
    {
        'd', Location(8, 0), 1,
        "There is an rune-carved dagger (d) here.",
        "You have an rune-carved dagger (d) stuck in your belt."
    },
    {
        'r', Location(9, 6), 10,
        "There is a diamond ring (r) here.",
        "You are wearing a diamond ring (r)."
    }
};


// helper function: to find every item at a location
// and print their descriptions
Item printItemDescription (const Location& loc) {
    for (const auto &arr : items) {
        if (arr.isAtLocation(loc))
            arr.printDescription();
    }
}


int main()
{
    // object of Item class
    Item item;
    // object of World class
    World my_world("ghostwood");
    // start node
    Location location(4, 1);

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

    // total points
    int total_points = 0;

     // game start message
    my_world.printStartMessage();

    // description for player current possition
    my_world.printDescription(location);
    printItemDescription(location);
    
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
            move_north = my_world.canGoNorth(location);
            if (move_north == true)
            {
                my_world.getNorth(location);
                my_world.printDescription(location);
            }
            else
                cout << "There is no way to go in that direction" << endl;
        }
        else if (input_str[0] == south) // south movement
        {
            move_south = my_world.canGoSouth(location);
            if (move_south == true)
            {
                my_world.getSouth(location);
                my_world.printDescription(location);
            }
            else
                cout << "There is no way to go in that direction" << endl;
        }
        else if (input_str[0] == east) // east movement
        {
            move_east = my_world.canGoEast(location);
            if (move_east == true)
            {
                my_world.getEast(location);
                my_world.printDescription(location);
            }
            else
                cout << "There is no way to go in that direction" << endl;
        }
        else if (input_str[0] == west) // west movement
        {
            move_west = my_world.canGoWest(location);
            if (move_west == true)
            {
                my_world.getWest(location);
                my_world.printDescription(location);
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
            
            if (player_input[0] == 's')
            {
                if (items[0].isInInventory() != true && 
                    items[0].isAtLocation(items[0].current_location) == true)
                {
                    items[0].moveToInventory();
                    total_points = total_points + items[0].getPlayerPoints();
                }
            }
            else if (player_input[0] == 'c')
            {
                if (items[1].isInInventory() != true && 
                    items[1].isAtLocation(items[1].current_location) == true)
                {
                    items[1].moveToInventory();
                    total_points = total_points + items[1].getPlayerPoints();
                }
            }
            else if (player_input[0] == 'k')
            {
                if (items[2].isInInventory() != true && 
                    items[2].isAtLocation(items[2].current_location) == true)
                {
                    items[2].moveToInventory();
                    total_points = total_points + items[2].getPlayerPoints();
                }
            }
            else if (player_input[0] == 't')
            {
                if (items[3].isInInventory() != true && 
                    items[3].isAtLocation(items[3].current_location) == true)
                {
                    items[3].moveToInventory();
                    total_points = total_points + items[3].getPlayerPoints();
                }
            }
            else if (player_input[0] == 'b')
            {
                if (items[4].isInInventory() != true && 
                    items[4].isAtLocation(items[4].current_location) == true)
                {
                    items[4].moveToInventory();
                    total_points = total_points + items[4].getPlayerPoints();
                }
            }
            else if (player_input[0] == 'm')
            {
                if (items[5].isInInventory() != true && 
                    items[5].isAtLocation(items[5].current_location) == true)
                {
                    items[5].moveToInventory();
                    total_points = total_points + items[5].getPlayerPoints();
                }
            }
            else if (player_input[0] == 'p')
            {
                if (items[6].isInInventory() != true && 
                    items[6].isAtLocation(items[6].current_location) == true)
                {
                    items[6].moveToInventory();
                    total_points = total_points + items[6].getPlayerPoints();
                }
            }
            else if (player_input[0] == 'd')
            {
                if (items[7].isInInventory() != true && 
                    items[7].isAtLocation(items[7].current_location) == true)
                {
                    items[7].moveToInventory();
                    total_points = total_points + items[7].getPlayerPoints();
                }
            }
            else if (player_input[0] == 'r')
            {
                if (items[8].isInInventory() != true && 
                    items[8].isAtLocation(items[8].current_location) == true)
                {
                    items[8].moveToInventory();
                    total_points = total_points + items[8].getPlayerPoints();
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
            
            if (player_input[0] == 's')
            {
                if (items[0].isInInventory() == true)
                {
                    total_points = total_points - items[0].getPlayerPoints();
                    items[0].moveToLocation(location);
                }
            }
            else if (player_input[0] == 'c')
            {
                if (items[1].isInInventory() == true)
                {
                    total_points = total_points - items[1].getPlayerPoints();
                    items[1].moveToLocation(location);
                }
            }
            else if (player_input[0] == 'k')
            {
                if (items[2].isInInventory() == true)
                {
                    total_points = total_points - items[2].getPlayerPoints();
                    items[2].moveToLocation(location);
                }
            }
            else if (player_input[0] == 't')
            {
                if (items[3].isInInventory() == true)
                {
                    total_points = total_points - items[3].getPlayerPoints();
                    items[3].moveToLocation(location);
                }
            }
            else if (player_input[0] == 'b')
            {
                if (items[4].isInInventory() == true)
                {
                    total_points = total_points - items[4].getPlayerPoints();
                    items[4].moveToLocation(location);
                }
            }
            else if (player_input[0] == 'm')
            {
                if (items[5].isInInventory() == true)
                {
                    total_points = total_points - items[5].getPlayerPoints();
                    items[5].moveToLocation(location);
                }
            }
            else if (player_input[0] == 'p')
            {
                if (items[6].isInInventory() == true)
                {
                    total_points = total_points - items[6].getPlayerPoints();
                    items[6].moveToLocation(location);
                }
            }
            else if (player_input[0] == 'd')
            {
                if (items[7].isInInventory() == true)
                {
                    total_points = total_points - items[7].getPlayerPoints();
                    items[7].moveToLocation(location);
                }
            }
            else if (player_input[0] == 'r')
            {
                if (items[8].isInInventory() == true)
                {
                    total_points = total_points - items[8].getPlayerPoints();
                    items[8].moveToLocation(location);
                }
            }
            else
                cout << "Invalid item" << endl;
        }
        else if (input_str[0] == 'i') // display the inventory
        {
            for (const auto &arr : items)
            {
                if (arr.isInInventory())
                    cout << arr.inventory_description << endl;
            }
        }
        else
        {
            cout << "Invalid command!" << endl;
            continue;
        }
        
        // check wether the player is at a death node
        is_death_node = my_world.isDeath(location);
        if (is_death_node == true) break;

        // check wether the player is at a victory node
        is_victory_node = my_world.isVictory(location);
        if (is_victory_node == true) break;
    }

    // game end message
    cout << endl;
    my_world.printEndMessage();
    cout << "In this game you scored " << total_points << " points." << endl;
}
