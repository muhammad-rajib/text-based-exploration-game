#pragma once

#include <string>
#include <iostream>
using namespace std;

#include "Location.h"

const char ID_NOT_INITIALIZED = '\0';


class Item {
    private:
        char id;
        
        Location start_location;
        Location current_location;

        bool is_in_inventory;
        int points;

        string world_description;
        string inventory_description;
    
    private:
        bool isInvariantTrue () const; // new in A3

    public:
        Item (); // new in A3
        Item (char id1,
                const Location& location,
                int points1,
                const string& world_description1,
                const string& inventory_description1);
        void debugPrint () const;
        bool isInitialized () const; // new in A3
        char getId () const;
        bool isInInventory () const;
        bool isAtLocation (const Location& location) const;
        int getPlayerPoints () const;
        void printDescription () const;
        bool operator < (const Item& other) const; // new in A3
        void reset ();
        void moveToInventory ();
        void moveToLocation (const Location& location);
};