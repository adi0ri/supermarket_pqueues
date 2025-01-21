//cust.cpp
//Ori, Aditya
//aori

#include <iostream>
#include <assert.h>
#include "cust.h"
using namespace std;

//Purpose: constructor
//Input parameters: string, bool, integer, integer
//Output parameters: none
//Return value: none
Cust::Cust(string name, bool is_robber, int arrival_time, int item_count){
    this->name=name;
    this->is_robber=is_robber;
    this->arrival_time=arrival_time;
    this->item_count=item_count;
}

//Purpose: gets the name of the customer
//Input parameters: none
//Output parameters: none
//Return value: string
string Cust::getName(){
    return name;
}

//Purpose: returns if robber or not
//Input parameters: none
//Output parameters: none
//Return value: bool
bool Cust::getIsRobber(){
    if (is_robber){
        return true;
    }
    return false;
}

//Purpose: gets the arrival time of the customer
//Input parameters: none
//Output parameters: none
//Return value: integer
int Cust::getArrivalTime(){
    return arrival_time;
}

//Purpose: gets the item count of the customer
//Input parameters: none
//Output parameters: none
//Return value: integer
int Cust::getItemCount(){
    return item_count;
}

//Purpose: prints the customers information in the given output file
//Input parameters: none
//Output parameters: output file
//Return value: none
void Cust::print(ostream &os){
    os<<name<<" ";
    if (is_robber){
        os<<"robber"<<" "<<arrival_time<<" "<<item_count<<endl;
    }
    else{
        os<<"shopper"<<" "<<arrival_time<<" "<<item_count<<endl;
    }
}

//Purpose: prints when customer enters shop
//Input parameters: integer
//Output parameters: output file
//Return value: none
void Cust::print_entershop(ostream &os,int clock){
    assert(clock == arrival_time );
    os<<clock<<": "<<name<<" entered store"<<endl;
}

//Purpose: prints when customer finishes shopping
//Input parameters: integer
//Output parameters: output file
//Return value: none
void Cust::print_finishshop(ostream &os,int clock){
    os<<clock<<": "<<name<<" done shopping"<<endl;
}

//Purpose: prints when customer starts checking
//Input parameters: integer, integer
//Output parameters: output file
//Return value: none
void Cust::print_startcheck(ostream &os,int clock,int checker_number){
    os<<clock<<": "<<name<<" started checkout with checker "<<checker_number<<endl;
}

//Purpose: prints how much cash the checker got or if the checker got robbed
//Input parameters: integer, integer, integer
//Output parameters: output file
//Return value: none
void Cust::print_endcheck(ostream &os,int clock,int checker_number,int cash){
    if (is_robber==true){
        if (item_count>1){
            os<<clock<<": "<<name<<" stole $"<<cash<<" and "<<item_count<<" items from checker "<<checker_number<<endl;
        }
        else{
            os<<clock<<": "<<name<<" stole $"<<cash<<" and "<<item_count<<" item from checker "<<checker_number<<endl;
        }

    }
    else{
        if (item_count>1){
            os<<clock<<": "<<name<<" paid $"<<cash<<" for "<<item_count<<" items to checker "<<checker_number<<endl;
        }
        else{
            os<<clock<<": "<<name<<" paid $"<<cash<<" for "<<item_count<<" item to checker "<<checker_number<<endl;
        }
    }
}