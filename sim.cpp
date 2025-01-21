//sim.cpp
//Ori, Aditya
//aori

#include <assert.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;
#include "cust.h"
#include "pqueue.h"

//defining constants
const int COST_PER_ITEM = 3;
const int SHOP_TIME_PER_ITEM = 2;
const int CHECKOUT_TIME_PER_ITEM = 1;
const int ROB_TIME = 7;
const int STARTING_CHECKER_CASH = 250;

//Purpose: checks if the input character string is an integer
//Input parameters: character string
//Output parameters: none
//Return value: bool
bool is_int(char str[])
{
	if (*str=='\0'){
		return true;
	}
	if (isdigit(*str)){
		str++;
		if (is_int(str)){
			return true;
		}
	}
	return false;
}

//Purpose: reads input into the priority queue customer objects
//Input parameters: none
//Output parameters: input file, priority queue
//Return value: none
void read_input(ifstream &ifile, PQueue &arrivaPQueue){
    string name;
    int arrival_time;
    string role;
    bool is_robber;
    int item_count;
    string cust_record;
    //taking customer information from input file in a loop
    while (ifile>>cust_record){
        name=cust_record;
        ifile>>role;
        if (role=="shopper"){
            is_robber=false;
        }
        else{
            is_robber=true;
        }
        ifile>>arrival_time;
        ifile>>item_count;
        arrivaPQueue.enqueue(new Cust(name, is_robber, arrival_time, item_count),arrival_time);
    }
}

//Purpose: runs the whole shopping/stealing simulation by printing all the actions along with timestamps in the output file
//Input parameters: integer, integer
//Output parameters: priority queue, output file
//Return value: none
void run_simulation(int checker_count, PQueue &arrivalPQueue, int checker_break_duration, ostream &os){
    struct Checker{
        int m_cash; // current cash (whole dollars) in this checkers register
        int m_done_time; // clock-tick checker will finish checking out current cust or will finish a break
        Cust *m_cust; // pointer to current customer being checked-out, or NULL if no cust being helped
    };
    Checker* checkers=new Checker[checker_count];
    //initializing checkers with default values
    for (int i=0;i<checker_count;i++){
        checkers[i].m_done_time=0;
        checkers[i].m_cash=STARTING_CHECKER_CASH;
        checkers[i].m_cust=NULL;
    }
    PQueue shopping_queue, checker_queue;
    int customer_count=arrivalPQueue.getSize();
    int clock;
    //main loop that runs the whole simulation with the clock
    for (clock = 1; customer_count > 0; clock++) {
        int prio;
        //customers going into the shop according to their arrival
        while (arrivalPQueue.getFirstPriority(prio) && prio==clock){
            if (clock==prio){
                Cust* arrived;
                if(arrivalPQueue.dequeue(arrived)){
                    int items=arrived->getItemCount();
                    int shopping_time=clock+items*SHOP_TIME_PER_ITEM;
                    arrived->print_entershop(os,clock);
                    shopping_queue.enqueue(arrived,shopping_time);
                }
            }
        }
        //customers finished shopping according to the number of items they purchased and getting into the checker queue
        while (shopping_queue.getFirstPriority(prio) && prio==clock){
            if (clock==prio){
                Cust* shopped;
                if (shopping_queue.dequeue(shopped)){
                    shopped->print_finishshop(os,clock);
                    checker_queue.enqueue(shopped,0);
                }
            }
        }
        //checking/stealing is done and checker is free or is in a break by running a loop through all checkers
        for (int i=0;i<checker_count;i++){
            if(checkers[i].m_cust!=NULL && checkers[i].m_done_time==clock){
                //if stolen, give checker break and reset checker cash to 0
                if (checkers[i].m_cust->getIsRobber()){
                    checkers[i].m_cust->print_endcheck(os,clock,i,checkers[i].m_cash);
                    checkers[i].m_cash=0;
                    checkers[i].m_done_time+=checker_break_duration;
                    customer_count--;
                    delete checkers[i].m_cust;
                    checkers[i].m_cust=NULL;
                }
                //if checked, give cash to checker and check-out customer
                else{
                    int items=checkers[i].m_cust->getItemCount();
                    checkers[i].m_cust->print_endcheck(os,clock,i,items*COST_PER_ITEM);
                    checkers[i].m_cash+=items*COST_PER_ITEM;
                    customer_count--;
                    delete checkers[i].m_cust;
                    checkers[i].m_cust=NULL;
                }
            }
        }
        //start checking/stealing if a checker is empty by running a loop through all checkers
        for(int i=0;i<checker_count;i++){
            if(checkers[i].m_cust==NULL && checkers[i].m_done_time<=clock){
                Cust* checking;
                if(checker_queue.dequeue(checking)){
                    checking->print_startcheck(os,clock,i);
                    checkers[i].m_cust=checking;
                    if (checking->getIsRobber()){
                        checkers[i].m_done_time=clock+ROB_TIME;
                    }
                    else{
                        int items=checking->getItemCount();
                        checkers[i].m_done_time=clock+items*CHECKOUT_TIME_PER_ITEM;
                    }
                }
            }
        }
    }
    //printing the final cash on every checker
    for (int i=0;i<checker_count;i++){
        os<<"registers["<<i<<"] = $"<<checkers[i].m_cash<<endl;
    }
    //freeing checkers' occupied heap memory
    delete[] checkers;
    os<<"time = "<<clock<<endl;
}

//Purpose: main function
//Input parameters: argc, argv
//Output parameters: none
//Return value: integer
int main(int argc, char* argv[]) {
    if (argc!=5){
        cerr<<"Error: invalid number of command line arguments."<<endl;
        exit(1);
    }
    int checker_count,checker_break_length;
    if (atoi(argv[1])<1 || !is_int(argv[1])){
        cerr<<"Error: invalid number of checkers specified."<<endl;
        exit(1);
    }
    else{
        checker_count=atoi(argv[1]);
    }
    if (atoi(argv[2])<0 || !is_int(argv[2])){
        cerr<<"Error: invalid checker break duration specified."<<endl;
        exit(1);
    }
    else{
        checker_break_length=atoi(argv[2]);
    }

    ifstream ifile(argv[3]);
    if (!ifile)
    {
        cerr << "Error: could not open input file <" << argv[3] << ">." << endl;
        exit(1);
    }

    ofstream ofile(argv[4], ios::out);
    if (!ofile)
    {
        cerr << "Error: could not open output file <" << argv[4] << ">." << endl;
        exit(1);
    }

    PQueue arrivalPQueue;
    read_input(ifile, arrivalPQueue);
    run_simulation(checker_count,arrivalPQueue,checker_break_length,ofile);

    return 0;
}