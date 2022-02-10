#pragma once

#include <string>
#include <iostream>
using namespace std;

struct Item
{
    char id;

    int start_row;
    int start_col;

    int curr_row;
    int curr_col;

    bool is_in_inventory;
    int points;

    string world_description;
    string inventory_description;
};

const char ID_NOT_INITIALIZED = '\0';


//
// itemInit
//
// Purpose: Initialize struct for items
// Parameter(s):
//  <1> id1: contain the char id for item.
//  <2> row1: .
// Precondition(s): value1 < upper1
// Returns: N/A
// Side effect: The counter is initialized, with value1 as 
//              the current counter value, and upper1 as the upper 
//              bound of counter values.
//
void itemInit (Item& item, 
            char id1, 
            int row1, int column1,
            int points1,
            const string& world_description1,
            const string& inventory_description1);
void itemDebugPrint (const Item& item);
char itemGetId (const Item& item);
bool itemIsInInventory (const Item& item);
bool itemIsAtLocation (const Item& item, int row, int column);
int itemGetPlayerPoints (const Item& item);
void itemPrintDescription (const Item& item);
void itemReset (Item& item);
void itemMoveToInventory (Item& item);
void itemMoveToLocation (Item& item, int row, int column);