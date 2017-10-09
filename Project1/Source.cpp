
#include <stdlib.h>
#include <iostream>
#include <exception>
#include "Elevator.h"
#include "Rider.h"
#include <time.h>
#include <list>


using namespace std;

int main() {
    srand(time(NULL));

    //scenario with 1 elevator
    Elevator e;
    e.set_location(0);
    int counter = 0,total_wait_time=0,total_riders=0;
    list <Rider> wait_list;
    cout << "Welcome to the elevator simulation! We currently have one elevator running." <<endl;
    cout << "Each tick represents 5 seconds. " << endl;
    cout << "The elevator can go to 1 floor per tick and every 3 ticks a new rider appears" << endl;
    cout << "The elevator can only hold 7 riders at a time" << endl;

    
  

    
    



    while (counter <= 60) {
        cout << "Tick # " << counter << endl;
        if (counter % 3== 0)//time for a new rider
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
            e.set_destination(i);
            if (e.destination > e.location)
            {
                e.set_direction("up");
            }
            else
                e.set_direction("down");
            
        }

        cout <<"Elevator at  "<< e.location << "  elevator going "<<e.direction<<" to " << e.destination<<endl;
        if (e.get_location() == e.get_destination())//time to stop and open doors
        {
            if (e.riders.size() == 0 && wait_list.size()>0)//picking up first rider
            {
                Rider r = wait_list.front();
                e.riders.push_back(r);
                wait_list.pop_front();
                e.set_destination(r.get_finish());
                cout << "New rider going " << r.direction << " from " << r.start << " to " << r.finish << endl;
               
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
                    it = e.riders.erase(it);
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
                
                int new_destination = e.riders.front().get_finish();//first person in line gets to choose which floor
                if (new_destination > e.get_location())
                {
                    e.set_direction("up");
                }
                else
                    e.set_direction("down");

                e.set_destination(new_destination);
            }
            else
                e.set_destination(0);//go back to lobby
        }



        if (wait_list.size() == 0)//if no riders, stay idle
        {
            
        }
        else if (e.get_direction() == "up")//elevator moves floors
        {
            if (e.location >= 6)//can't go past 6
            {
                e.set_direction("down");
            }
            else {
                int i = e.get_location();
                i += 1;
                e.set_location(i);
            }
            
        }
        else if (e.get_direction() == "down")
        {
            if (e.location <= 0)
            {
                e.set_direction("up");//elevator can't go negative floors
            }
            else {
                int i = e.get_location();//elevator goes down 1 floor
                i -= 1;
                e.set_location(i);
            }
        }

        for (list<Rider>::iterator it = e.riders.begin(); it != e.riders.end(); ++it)
        {
            it->increment_wait_time();//each tick the wait time is incremented for all riders in elevator
        }
        for (list<Rider>::iterator it = wait_list.begin(); it != wait_list.end(); ++it)
        {
            it->increment_wait_time();//each tick the wait time is incremented for all riders waiting
        }

        
        cout << endl<<"There are " << e.riders.size() << " Riders in the elevator and " << wait_list.size() << " riders waiting" << endl;
        counter++;
    }
 
    cout << "The wait time for "<<total_riders<<" finished riders is: " << total_wait_time << endl;
    cout << "The average wait for these riders is " << (total_wait_time / total_riders) << endl;
    int final_wait_time=0;
    for (list<Rider>::iterator it = e.riders.begin(); it != e.riders.end(); ++it)//calculate wait time for riders in line
    {
        final_wait_time += it->wait_time;
    }
    for (list<Rider>::iterator it = wait_list.begin(); it != wait_list.end(); ++it)
    {
        final_wait_time += it->wait_time;
    }
    cout << "Of the " << (e.riders.size()+wait_list.size())<<" riders still waiting, their wait time is: " << final_wait_time<<endl;
    cout << "The average wait for these riders is " << (final_wait_time / (e.riders.size() + wait_list.size())) << endl << endl;;

//scenario with 2 elevators
    Elevator e1, e2;
    e1.set_location(0);
    e2.set_location(0);
    int counter2 = 0, total_wait_time2 = 0;
    list <Rider> wait_list2;
    list<Rider> e1_temp_list;
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
        if (e1.riders.size() == 0 && wait_list2.size()>0&&e1_temp_list.size()==0)//if no one on elevator, go to wait line
        {
            Rider r = wait_list2.front();
            int i = r.get_start();
            e1.set_destination(i);
            e1_temp_list.push_back(r);
            wait_list2.pop_front();
            cout << "new rider in elevator 1 going " << r.direction << " from " << r.start << "  to " << r.finish << endl;
        }
        else if (e2.riders.size() == 0 && wait_list2.size()>0 &&e2_temp_list.size()==0)//if no one on elevator, go to wait line
        {
            Rider r = wait_list2.front();
            int i = r.get_start();
            e2.set_destination(i);
            e2_temp_list.push_back(r);
            wait_list2.pop_front();
            cout << "new rider in elevator 2 going " << r.direction << " from " << r.start << "  to " << r.finish << endl;
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
                cout << "One rider got on at floor " << e1.location << endl;
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
                        cout << "one rider got off at floor " << e1.location << endl;

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
                            cout << "One rider got on at floor " << e1.location<<endl;
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
       
        
            cout << "2nd elevator at  " << e2.location << "  elevator going " << e2.direction << " to " << e2.destination<<endl;
            if (e2.get_location() == e2.get_destination())//time to stop and open doors
            {
                if (e2.riders.size() == 0 && e2_temp_list.size()>0)//picking up first rider
                {
                    Rider r = e2_temp_list.front();
                    e2.riders.push_back(r);
                    e2_temp_list.pop_front();
                    e2.set_destination(r.get_finish());
                    cout << "One rider got on at floor " << e2.location << endl;
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
                    cout << "one rider got off at floor " << e2.location << endl;

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
                        cout << "One rider got on at floor " << e2.location;
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



        
       if (e1.get_direction() == "up")//elevator moves floors
        {
            if (e1.location >= 6)//can't go past 6
            {
                e1.set_direction("down");
            }
            else {
                int i = e1.get_location();
                i += 1;
                e1.set_location(i);
            }

        }
        else if (e1.get_direction() == "down")
        {
            if (e1.location <= 0)
            {
                e1.set_direction("up");//elevator can't go negative floors
            }
            else {
                int i = e1.get_location();//elevator goes down 1 floor
                i -= 1;
                e1.set_location(i);
            }
        }
       
         if (e2.get_direction() == "up")//elevator moves floors
        {
            if (e2.location >= 6)//can't go past 6
            {
                e2.set_direction("down");
            }
            else {
                int i = e2.get_location();
                i += 1;
                e2.set_location(i);
            }

        }
        else if (e2.get_direction() == "down")
        {
            if (e2.location <= 0)
            {
                e2.set_direction("up");//elevator can't go negative floors
            }
            else {
                int i = e2.get_location();//elevator goes down 1 floor
                i -= 1;
                e2.set_location(i);
            }
        }

        for (list<Rider>::iterator it = e1.riders.begin(); it != e1.riders.end(); ++it)
        {
            it->increment_wait_time();//each tick the wait time is incremented for all riders in elevator
        }
        for (list<Rider>::iterator it = wait_list2.begin(); it != wait_list2.end(); ++it)
        {
            it->increment_wait_time();//each tick the wait time is incremented for all riders waiting
        }
        for (list<Rider>::iterator it = e2.riders.begin(); it != e2.riders.end(); ++it)
        {
            it->increment_wait_time();//each tick the wait time is incremented for all riders in elevator
        }
       


       
        cout <<endl<<"There are " << e1.riders.size() << " Riders in the first elevator and " << e2.riders.size();
        cout <<" riders in the 2nd elevator and "<< wait_list2.size() << " riders waiting" << endl;
        cout << "The total wait time is  " << total_wait_time2 << endl;
        counter2++;
    }
    cout << "There are " << e1.riders.size() << " in elevator 1, " << e2.riders.size() << " riders in elevator 2 and ";
        cout << wait_list2.size() << " still waiting" << endl;
    cout << "The wait time for finished riders is: " << total_wait_time2 << endl;
    int final_wait_time2 = 0;
    for (list<Rider>::iterator it = e1.riders.begin(); it != e1.riders.end(); ++it)
    {
        final_wait_time2 += it->wait_time;
    }
    for (list<Rider>::iterator it = e2.riders.begin(); it != e2.riders.end(); ++it)
    {
        final_wait_time2 += it->wait_time;
    }
    for (list<Rider>::iterator it = wait_list2.begin(); it != wait_list2.end(); ++it)
    {
        final_wait_time2 += it->wait_time;
    }
    cout << "Of the riders still waiting, their wait time is: " << final_wait_time << endl;


    system("pause");

    return 0;
}

