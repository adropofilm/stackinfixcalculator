#pragma once
#include <string>

using namespace std;
class Rider
{

public:
    Rider() { wait_time = 0; }
    Rider(int i, int i2) { start = i, finish = i2, wait_time = 0; }
    int start,finish,wait_time;//floor rider starts at, floor they are going to, how long they waited
    string direction;//up or down
    //getters
    string get_direction() { return direction; }
    int get_start() { return start; }
    int get_finish() { return finish; }
    //setters
    void set_direction(string s) { direction = s; }
    void set_start(int i) { start = i; }
    void set_finish(int i) { finish = i; }
    void increment_wait_time() { wait_time += 1; }//each tick the riders time is incremented
    const Rider& operator= (const Rider& rhs);
    bool Rider::operator==(Rider rhs);

};


const Rider& Rider::operator=(const Rider& rhs)
{
    if (this != &rhs)
    {
        start = rhs.start;
        finish = rhs.finish;
        wait_time = rhs.wait_time;
        direction = rhs.direction;
    }
    return *this;
}

bool Rider::operator==(Rider rhs)
{
    
    return ((start == rhs.start) && (finish == rhs.finish) && (direction == rhs.direction) && (wait_time == rhs.wait_time));
}