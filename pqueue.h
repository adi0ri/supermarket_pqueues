//pqueue.h
//Ori, Aditya
//aori

#ifndef PQUEUE_H
#define PQUEUE_H

#include"cust.h"

class PQueue{
    private:
    class Node{
        public:
        Cust* cust;
        int priority;
        Node* next;
        Node(Cust* cust, int priority, Node* next) : cust(cust), priority(priority), next(next){}
    };
    Node* head;
    public:

    PQueue(): head(nullptr) {}
    void enqueue(Cust* cust, int priority);
    bool dequeue(Cust* &cust_out);
    bool isEmpty();
    bool getFirstPriority(int &priority_out);
    int getSize();
    void print(ostream &os);
};

#endif