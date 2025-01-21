//cust.h
//Ori, Aditya
//aori

#ifndef CUST_H
#define CUST_H
#include <string>
using namespace std;

class Cust{
    private:
    string name;
    bool is_robber;
    int arrival_time, item_count;

    public:
    Cust(string name, bool is_robber, int arrival_time, int item_count);
    string getName();
    bool getIsRobber();
    int getArrivalTime();
    int getItemCount();
    void print(ostream &os);
    void print_entershop(ostream &os,int clock);
    void print_finishshop(ostream &os,int clock);
    void print_startcheck(ostream &os,int clock,int checker_number);
    void print_endcheck(ostream &os,int clock,int checker_number,int cash);
};


#endif