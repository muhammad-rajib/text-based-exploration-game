#pragma once

#include <string>
#include <iostream>
using namespace std;


class Location {
    public:
        int row;
        int column;
    
        Location();

        Location (int row1, int column1);
        bool operator == (const Location& other) const;
};

ostream& operator<< (ostream& out, const Location& location);