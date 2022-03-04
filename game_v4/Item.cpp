#include <string>
#include <iostream>
#include <cassert>
using namespace std;

#include "Item.h"



Item::Item()
    : id(ID_NOT_INITIALIZED),
        is_in_inventory(false),
        points(0),
        world_description("[Item not initialized]"),
        inventory_description("[Item not initialized]"),
        start_location(Location()),
        current_location(Location()) 
{
    assert (isInvariantTrue());
}

Item::Item (char id1,
            const Location& location,
            int points1,
            const string& world_description1,
            const string& inventory_description1)
{

    if (ID_NOT_INITIALIZED == '\0')
        is_in_inventory = false;
    else
        is_in_inventory = true;
    
    id = id1;
    start_location = location;
    current_location = location;
    points = points1;
    world_description = world_description1;
    inventory_description = inventory_description1;

    assert (isInvariantTrue());
}

bool Item::operator < (const Item& other) const
{
    if (id < other.id)
        return true;
    else
        return false;
}

bool Item::isInvariantTrue () const{
    if (world_description == "")
        return false;
    if (inventory_description == "")
        return false;
    return true;
}

void Item::debugPrint()const {
    cout << "id:\t" << "\'" << id << "\'" << endl;
    cout << "start_location:\t(row = " << start_location.row << ", column = " << start_location.column << ")" << endl;
    cout << "current_location:\t(row = " << current_location.row << ", column = " << current_location.column << ")" << endl;
    cout << "is_in_inventory:\t" << is_in_inventory << endl;
    cout << "points:\t" << points << endl;
    cout << "world_description:\t" << "\"" << world_description << "\"" << endl;
    cout << "inventory_description:\t" << "\"" << inventory_description << "\"" << endl;
}

bool Item::isInitialized () const{
    assert (isInvariantTrue());
    if (id == ID_NOT_INITIALIZED)
        return false;
    else
        return true;
}

char Item::getId () const{
    assert (isInvariantTrue());
    return id;
}

bool Item::isInInventory () const{
    assert (isInvariantTrue());
    return is_in_inventory;
}

bool Item::isAtLocation (const Location& location) const{
    assert (isInvariantTrue());
    if (!(current_location == location)) 
        return false;
    else
        return true;
}

int Item::getPlayerPoints () const{
    assert (isInvariantTrue());
    if (is_in_inventory == true)
        return points;
    return 0;
}

void Item::printDescription () const{
    assert (isInvariantTrue());
    if (is_in_inventory == true)
        cout << inventory_description << endl;
    else
        cout << world_description << endl;
}

void Item::reset () {
    current_location = Location(start_location.row, start_location.column);
    is_in_inventory = false;
    assert (isInvariantTrue());
}

void Item::moveToInventory () {
    is_in_inventory = true;
    assert (isInvariantTrue());
}

void Item::moveToLocation (const Location& location) 
{   
    current_location = Location(location.row, location.column);
    is_in_inventory = false;
    assert (isInvariantTrue());
}