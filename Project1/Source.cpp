
#include <stdlib.h>
#include <iostream>
#include <exception>
#include "Elevator.h"
#include "Rider.h"
#include <time.h>
#include <list>



//Problem: Create an elevator simulator that is first come first serve but prioritizes 
// riders whose destination is on the way


using namespace std;

void move_up(Elevator& e)//moves the elevator up 1 floor
{
    if (e.location >= 6)//can't go past 6
    {
        e.set_direction("down");
    }
    else {
       e.go_up();
    }
}
void move_down(Elevator& e)//moves the elevator down 1 floor
{
    if (e.location <= 0)
    {
        e.set_direction("up");//elevator can't go negative floors
    }
    else {
        e.go_down();
    }
}

void increment_list_wait_time(list <Rider>& lst)
//iterates through a list of riders and increments the wait time for each rider
{
    for (list<Rider>::iterator it = lst.begin(); it != lst.end(); ++it)
    {
        it->increment_wait_time();
    }
}

void calculate_wait_time(list <Rider> lst, int& i)//iterates through the list and calculates
//the wait time for all riders in the list
{
    for (list<Rider>::iterator it = lst.begin(); it != lst.end(); ++it)
    {
        i += it->wait_time;
    }
}

int main() {
    srand(time(NULL));

    //scenario with 1 elevator
    Elevator e;
    int counter = 0,total_wait_time=0,total_riders=0;
    list <Rider> wait_list;//hold riders waiting to get on elevator
    cout << "Welcome to the elevator simulation! We currently have one elevator running." <<endl;
    cout << "Each tick represents 5 seconds. " << endl;
    cout << "The elevator can go to 1 floor per tick and every 2 ticks a new rider appears" << endl;
    cout << "The elevator can only hold 7 riders at a time" << endl;

    
  

    
    



    while (counter <= 30) {
        cout <<endl<< "Tick # " << counter <<endl;
        if (counter % 2== 0)//time for a new rider
        {
            int start, end;
            string direction;
            start = rand() % 6;
            end = rand() % 6;
            while (start == end)//can't go to same floor
            {
                end = rand() % 6;
            }
            if (start > end)
                direction = "down";
            else
                direction = "up";
            Rider r(start,end);
            r.set_direction(direction);
            wait_list.push_back(r);

           
        }
        if (e.riders.size() == 0 && wait_list.size()>0)//if no one on elevator, go to wait line
        {
            Rider r = wait_list.front();
            int i = r.get_start();
            e.set_destination(i);//go to pick up first rider
            if (e.destination > e.location)
            {
                e.set_direction("up");
            }
            else
                e.set_direction("down");
            
        }

        cout <<"Elevator at  "<< e.location << "  elevator going "<<e.direction<<" to " << e.destination<<endl;
        if (e.get_location() == e.get_destination())//time to stop and open doors to pick up/drop off first in line
        {
            if (e.riders.size() == 0 && wait_list.size()>0)//picking up first rider
            {
                Rider r = wait_list.front();
                e.riders.push_back(r);// pick up rider
                wait_list.pop_front();// rider no longer waiting
                e.set_destination(r.get_finish());
                cout << "One rider got on at floor " << e.get_location() << endl;
               
                if (e.destination < e.location)
                {
                    e.set_direction("down");
                }
                else
                    e.set_direction("up");
               
            }
            
            //check if anyone is getting off on this floor
            for (list<Rider>::iterator it = e.riders.begin(); it != e.riders.end();)
            {
                
                if (it->finish == e.get_location())
                {
                    
                    total_wait_time += it->wait_time;//keep track of everyone's wait time
                    total_riders += 1;
                    it = e.riders.erase(it);//rider exits elevator
                    cout << "One rider got off at floor " << e.location<<endl;

                }
                else
                    ++it;
            }
            if (e.riders.size() <= 6)//can pick up more riders
            {
                for (list<Rider>::iterator it = wait_list.begin(); it != wait_list.end();)
                {
                    
                    if ((it->start == e.get_location()) && (it->direction == e.get_direction()))
                        //check if anyone is waiting to get on at this floor and going same way(up/down)
                    {
                        
                        Rider r = *it;
                        e.riders.push_back(r);//person gets on elevator at end of queue
                        it = wait_list.erase(it);//rider no longer waiting
                        cout << "One rider got on at floor " << e.location<<endl;
                    }
                    else
                        it++;
                }
            }
            if (e.riders.size() > 0) {
                
                int new_destination = e.riders.front().get_finish();//first person in line gets 
                //to choose which floor to go to
                if (new_destination > e.get_location())
                {
                    e.set_direction("up");
                }
                else
                    e.set_direction("down");

                e.set_destination(new_destination);
            }
            else
                e.set_destination(0);//go back to lobby to wait for riders
        }
        else {//check to see if anyone on elevator getting off on this floor, or if anyone getting on
            for (list<Rider>::iterator it = e.riders.begin(); it != e.riders.end();)//
            {

                if (it->finish == e.get_location())
                {

                    total_wait_time += it->wait_time;//keep track of everyone's wait time
                    total_riders += 1;
                    it = e.riders.erase(it);
                    cout << "One rider got off at floor " << e.location << endl;

                }
                else
                    ++it;
            }
            if (e.riders.size() <= 6)//can pick up more riders
            {
                for (list<Rider>::iterator it = wait_list.begin(); it != wait_list.end();)
                {

                    if ((it->start == e.get_location()) && (it->direction == e.get_direction()))
                        //check if anyone is waiting to get on at this floor and going same way(up/down)
                    {

                        Rider r = *it;
                        e.riders.push_back(r);//person gets on elevator at end of queue
                        it = wait_list.erase(it);//rider no longer waiting
                        cout << "One rider got on at floor " << e.location << endl;
                    }
                    else
                        it++;
                }
            }
        }

        if (wait_list.size() == 0 && e.riders.size()==0)//if no riders, stay idle
        {
            
        }
        else if (e.get_direction() == "up")//elevator moves floors
        
            move_up(e);
            
        
        else if (e.get_direction() == "down")
        {
            move_down(e);
        }

        increment_list_wait_time(e.riders);
        increment_list_wait_time(wait_list);

        
        cout <<"There are " << e.riders.size() << " Riders in the elevator and " << wait_list.size() << " riders waiting" << endl;
        counter++;
    }
 
    cout <<endl<< "The wait time for "<<total_riders <<" finished riders is: " << total_wait_time << endl;
    cout << "The average wait for these riders is " << (total_wait_time / total_riders) << endl;
    int final_wait_time=0;//wait time for riders still in elevator/line
    calculate_wait_time(e.riders,final_wait_time);
    calculate_wait_time(wait_list, final_wait_time);
    cout << "Of the " << (e.riders.size()+wait_list.size())<<" riders still waiting, their wait time is: " << final_wait_time<<endl;
    cout << "The average wait for these riders is " << (final_wait_time / (e.riders.size() + wait_list.size())) << endl << endl;;

//scenario with 2 elevators
    Elevator e1, e2;
 
    int counter2 = 0, total_wait_time2 = 0,total_riders2=0;
    list <Rider> wait_list2;
    list<Rider> e1_temp_list;//this list holds the riders between when the request is made
    //and when the elevator arrives to pick the rider up, to keep the riders seperate for each elevator
    list<Rider> e2_temp_list;
    cout << "Welcome to the elevator simulation! We currently have 2 elevators running." << endl;
    cout << "Each tick represents 5 seconds. " << endl;
    cout << " The elevators can go to 1 floor per tick and every tick a new rider appears" << endl;
    cout << "The elevator can only hold 7 riders at a time" << endl << endl;









 while (counter2 <= 30) {
     cout <<endl<< "Tick # "<< counter2 << endl;
        if (counter2 % 1 == 0)//time for a new rider
        {
            int start, end;
            string direction;
            start = rand() % 6;
            end = rand() % 6;
            while (start == end)//can't go to same floor
            {
                end = rand() % 6;
            }
            if (start > end)
                direction = "down";
            else
                direction = "up";
            Rider r(start, end);
            r.set_direction(direction);
            wait_list2.push_back(r);


        }
        if (e1.riders.size() == 0 && wait_list2.size()>0&& e1_temp_list.size()==0)//if no one on elevator, go to wait line
        {
            Rider r = wait_list2.front();
            int i = r.get_start();
            e1.set_destination(i);
            e1_temp_list.push_back(r);
            wait_list2.pop_front();
            
        }
        else if (e2.riders.size() == 0 && wait_list2.size()>0 &&e2_temp_list.size()==0)//if no one on elevator, go to wait line
        {
            Rider r = wait_list2.front();
            int i = r.get_start();
            e2.set_destination(i);
            e2_temp_list.push_back(r);
            wait_list2.pop_front();
          
        }
        

        cout << "First elevator at  " << e1.location << "  elevator going " << e1.direction << " to " << e1.destination << endl;
        if (e1.get_location() == e1.get_destination())//time to stop and open doors
        {
            if (e1.riders.size() == 0 && e1_temp_list.size()>0)//picking up first rider
            {
                Rider r = e1_temp_list.front();
                e1.riders.push_back(r);
                e1_temp_list.pop_front();
                e1.set_destination(r.get_finish());
                cout << "One rider got on first elevator at floor " << e1.location << endl;
                if (e1.destination < e1.location)
                {
                    e1.set_direction("down");
                }
                else
                    e1.set_direction("up");
                //check if anyone is getting off on this floor
                for (list<Rider>::iterator it = e1.riders.begin(); it != e1.riders.end();)
                {

                    if (it->finish == e1.get_location())
                    {

                        total_wait_time2 += it->wait_time;//keep track of everyone's wait time
                        it = e1.riders.erase(it);
                        total_riders2 += 1;
                        cout << "one rider got off first elevator at floor " << e1.location << endl;

                    }
                    else
                        ++it;
                }
                if (e1.riders.size() <= 6)//can pick up more riders
                {
                    for (list<Rider>::iterator it = wait_list2.begin(); it != wait_list2.end();)
                    {

                        if ((it->start == e1.get_location()) && (it->direction == e1.get_direction()))
                            //check if anyone is waiting to get on at this floor and going same way(up/down)
                        {

                            Rider r = *it;
                            e1.riders.push_back(r);//person gets on elevator at end of queue
                            it = wait_list2.erase(it);//rider no longer waiting
                            cout << "One rider got on first elevator at floor " << e1.location<<endl;
                        }
                        else
                            it++;
                    }
                }
                if (e1.riders.size() > 0) {

                    int new_destination = e1.riders.front().get_finish();//first person in line gets to choose which floor
                    if (new_destination > e1.get_location())
                    {
                        e1.set_direction("up");
                    }
                    else
                        e1.set_direction("down");

                    e1.set_destination(new_destination);
                }
                else
                    e1.set_destination(0);//go back to lobby
            }

            }
        else {
            for (list<Rider>::iterator it = e1.riders.begin(); it != e1.riders.end();)//
            {

                if (it->finish == e1.get_location())
                {

                    total_wait_time2 += it->wait_time;//keep track of everyone's wait time
                    total_riders2 += 1;
                    it = e1.riders.erase(it);
                    cout << "One rider got off first elevator at floor " << e1.location << endl;

                }
                else
                    ++it;
            }
            if (e1.riders.size() <= 6)//can pick up more riders
            {
                for (list<Rider>::iterator it = wait_list2.begin(); it != wait_list2.end();)
                {

                    if ((it->start == e1.get_location()) && (it->direction == e1.get_direction()))
                        //check if anyone is waiting to get on at this floor and going same way(up/down)
                    {

                        Rider r = *it;
                        e1.riders.push_back(r);//person gets on elevator at end of queue
                        it = wait_list2.erase(it);//rider no longer waiting
                        cout << "One rider got on first elevator at floor " << e1.location << endl;
                    }
                    else
                        it++;
                }
            }
        }
       
        
            cout << "2nd elevator at  " << e2.location << "  elevator going " << e2.direction << " to " << e2.destination<<endl;
            if (e2.get_location() == e2.get_destination())//time to stop and open doors
            {
                if (e2.riders.size() == 0 && e2_temp_list.size()>0)//picking up first rider
                {
                    Rider r = e2_temp_list.front();
                    e2.riders.push_back(r);
                    e2_temp_list.pop_front();
                    e2.set_destination(r.get_finish());
                    cout << "One rider got on second elevator at floor " << e2.location << endl;
                    if (e2.destination < e2.location)
                    {
                        e2.set_direction("down");
                    }
                    else
                        e2.set_direction("up");

                }

            
            for (list<Rider>::iterator it = e2.riders.begin(); it != e2.riders.end();)
            {

                if (it->finish == e2.get_location())
                {

                    total_wait_time2 += it->wait_time;//keep track of everyone's wait time
                    it = e2.riders.erase(it);
                    total_riders2 += 1;
                    cout << "one rider got off second elevator at floor " << e2.location << endl;

                }
                else
                    ++it;
            }
            if (e2.riders.size() <= 6)//can pick up more riders
            {
                for (list<Rider>::iterator it = wait_list2.begin(); it != wait_list2.end();)
                {

                    if ((it->start == e2.get_location()) && (it->direction == e2.get_direction()))
                        //check if anyone is waiting to get on at this floor and going same way(up/down)
                    {

                        Rider r = *it;
                        e2.riders.push_back(r);//person gets on elevator at end of queue
                        it = wait_list2.erase(it);//rider no longer waiting
                        cout << "One rider got on first elevator at floor " << e2.location;
                    }
                    else
                        it++;
                }
            }
            if (e2.riders.size() > 0) {

                int new_destination = e2.riders.front().get_finish();//first person in line gets to choose which floor
                if (new_destination > e2.get_location())
                {
                    e2.set_direction("up");
                }
                else
                    e2.set_direction("down");

                e2.set_destination(new_destination);
            }
            else
                e2.set_destination(0);//go back to lobby
        }
            else {
                for (list<Rider>::iterator it = e2.riders.begin(); it != e2.riders.end();)//
                {

                    if (it->finish == e2.get_location())
                    {

                        total_wait_time2 += it->wait_time;//keep track of everyone's wait time
                        total_riders2 += 1;
                        it = e2.riders.erase(it);
                        cout << "One rider got off second elevator at floor " << e2.location << endl;

                    }
                    else
                        ++it;
                }
                if (e2.riders.size() <= 6)//can pick up more riders
                {
                    for (list<Rider>::iterator it = wait_list2.begin(); it != wait_list2.end();)
                    {

                        if ((it->start == e2.get_location()) && (it->direction == e2.get_direction()))
                            //check if anyone is waiting to get on at this floor and going same way(up/down)
                        {

                            Rider r = *it;
                            e2.riders.push_back(r);//person gets on elevator at end of queue
                            it = wait_list2.erase(it);//rider no longer waiting
                            cout << "One rider got on second elevator at floor " << e2.location << endl;
                        }
                        else
                            it++;
                    }
                }
            }



        
        if (e1.get_direction() == "up")//elevator moves floors
             move_up(e1);
        else if (e1.get_direction() == "down")
             move_down(e1);
        
       
        if (e2.get_direction() == "up")//elevator moves floors
            move_up(e2);
        else if (e2.get_direction() == "down")
            move_down(e2);
        

        increment_list_wait_time(e1.riders);//each tick wait time is incremented for all riders
        increment_list_wait_time(e2.riders);
        increment_list_wait_time(wait_list2);


       
        cout <<"There are " << e1.riders.size() << " Riders in the first elevator and " << e2.riders.size();
        cout <<" riders in the 2nd elevator and "<< wait_list2.size() << " riders waiting" << endl;
       
        counter2++;
    }
    cout << "There are " << e1.riders.size() << " in elevator 1, " << e2.riders.size() << " riders in elevator 2 and ";
        cout << wait_list2.size() << " still waiting" << endl;
    cout << "The wait time for " << total_riders2<< " finished riders is: " << total_wait_time2 << endl;
    cout << "Their average wait time is " << (total_wait_time2 / total_riders2) << endl;
    int final_wait_time2 = 0;
    calculate_wait_time(e1.riders, final_wait_time2);//calculate the wait for the riders still on elevators
    calculate_wait_time(e2.riders, final_wait_time2);
    calculate_wait_time(wait_list2, final_wait_time2);//calculate the wait for riders in line
   
    cout << "Of the riders still waiting, their wait time is: " << final_wait_time2 << endl;
    cout << "The average for these riders still waiting is " << (final_wait_time2 / (e1.riders.size() + e2.riders.size() + wait_list2.size()))<<endl;


    system("pause");

    return 0;
}

