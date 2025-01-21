//pqueue.cpp
//Ori, Aditya
//aori
#include <iostream>
#include "cust.h"
#include "pqueue.h"

//Purpose: inserts according to priority into the priority queue
//Input parameters: customer object pointer, integer
//Output parameters: none
//Return value: none
void PQueue::enqueue(Cust* cust, int priority){
    Node* newNode = new Node(cust, priority, nullptr);

    if (!head || priority < head->priority) {
        newNode->next = head;
        head = newNode;
    } 
    else {
        Node* current = head;
        while (current->next && priority >= current->next->priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

//Purpose: removes head and returns the element and frees the memory
//Input parameters: none
//Output parameters: customer object
//Return value: bool
bool PQueue::dequeue(Cust* &cust_out){
    if (!head) {
        return false;
    }
    Node* temp= head;
    cust_out=temp->cust;
    head = head->next;
    delete temp;
    return true;
}

//Purpose: checks if the priority queue is empty
//Input parameters: none
//Output parameters: none
//Return value: bool
bool PQueue::isEmpty(){
    if (head==nullptr){
        return true;
    }
    return false;
}

//Purpose: returns the head elements priority
//Input parameters: none
//Output parameters: integer
//Return value: bool
bool PQueue::getFirstPriority(int &priority_out){
    if (head==nullptr){
        return false;
    }
    priority_out=head->priority;
    return true;
}

//Purpose: returns the current size of the priority queue
//Input parameters: none
//Output parameters: none
//Return value: integer
int PQueue::getSize(){
    if(head==nullptr){
        return 0;
    }
    Node* temp=head;
    int count=0;
    while(temp!=nullptr){
        count++;
        temp=temp->next;
    }
    return count;
}

//Purpose: prints the whole priority queue in the given output file
//Input parameters: none
//Output parameters: output file
//Return value: none
void PQueue::print(ostream &os){
    if(head==nullptr){
        return;
    }
    Node* temp=head;
    while(temp!=nullptr){
        temp->cust->print(os);
        temp=temp->next;
    }
}
