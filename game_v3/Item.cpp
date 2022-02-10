#include <string>
#include <iostream>
#include <assert.h>

#include "Item.h"

using namespace std;


void itemInit (Item& item, 
            char id1, 
            int row1, int column1,
            int points1,
            const string& world_description1,
            const string& inventory_description1) 
{
    assert(id1 != ID_NOT_INITIALIZED);
    assert(world_description1 != "");
    assert(inventory_description1 != "");

    if (ID_NOT_INITIALIZED == '\0')
        item.is_in_inventory = false;
    else
        item.is_in_inventory = true;

    item.id = id1;
    item.start_row = row1;
    item.start_col = column1;
    item.curr_row = row1;
    item.curr_col = column1;
    item.points = points1;
    item.world_description = world_description1;
    item.inventory_description = inventory_description1;
}

void itemDebugPrint (const Item& item) {
    cout << "id:\t" << "\'" << item.id << "\'" << endl;
    cout << "start_row:\t" << item.start_row << endl;
    cout << "start_column:\t" << item.start_col << endl;
    cout << "current_row:\t" << item.curr_row << endl;
    cout << "current_column:\t" << item.curr_col << endl;
    cout << "is_in_inventory:\t" << item.is_in_inventory << endl;
    cout << "points:\t" << item.points << endl;
    cout << "world_description:\t" << "\"" << item.world_description << "\"" << endl;
    cout << "inventory_description:\t" << "\"" << item.inventory_description << "\"" << endl;
}

char itemGetId (const Item& item) {
    return item.id;
}

bool itemIsInInventory (const Item& item) 
{
    return item.is_in_inventory;
}

bool itemIsAtLocation (const Item& item, int row, int column) {
    if (item.curr_row == row && item.curr_col == column) 
        return true;
    else
        return false;
}

int itemGetPlayerPoints (const Item& item) {
    if (item.is_in_inventory == true)
        return item.points;
    else if (item.is_in_inventory == false)
        return 0;
}

void itemPrintDescription (const Item& item) {
    if (item.is_in_inventory == true)
        cout << item.inventory_description << endl;
    else
        cout << item.world_description << endl;
}

void itemReset (Item& item) 
{
    item.curr_row = item.start_row;
    item.curr_col = item.start_col;
    item.is_in_inventory = false;
}

void itemMoveToInventory (Item& item) 
{
    item.is_in_inventory = true;
}

void itemMoveToLocation (Item& item, int row, int column) 
{
    item.curr_row = row;
    item.curr_col = column;
    item.is_in_inventory = false;
}