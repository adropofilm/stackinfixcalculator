#include <string>
#include "Rider.h"
#include <list>


#pragma once


using namespace std;

class Elevator
{
public:
        Elevator(){ location = 0,direction = "up"; }//elevator starts on ground floor
        list <Rider> riders;
        int destination, location;
        string direction;
        //getters
        int get_destination() { return destination; }
        int get_location() { return location; }
        string get_direction() { return direction; }
        //setters
        void set_destination(int i) { destination = i; }
        void set_location(int i) { location = i; }
        void set_direction(string s) { direction = s; }

};