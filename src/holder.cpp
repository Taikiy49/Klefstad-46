// modules
#include "holder.h"
#include "Timer.h"
// my other imports I'm gonna useee
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ARRAYSTACK -----
// constructor (set the values to what they should be initially)
ArrayStack::ArrayStack(int cap)
    :Stack("Array"), capacity(cap), size(0), buf(new string[cap])
{}

void ArrayStack::push(const string & word){
    if (!is_full()) buf[size++] = word; // the conditional is important because pushing when it's already full will cause a problem. 
}
void ArrayStack::pop(){
    if (!is_empty()) --size; // the conditional is important because popping when it's empty will also cause a problem. 
}
string ArrayStack::top(){
    if (!is_empty()) return buf[size-1]; // size-1 to account for the nullptr
    return ""; 
}
bool ArrayStack::is_empty(){ return size == 0; }
bool ArrayStack::is_full(){ return size == capacity; }

// if elements are 1, 2, 3
// it will print 3, 2, 1
// this makes sense because 3 was the last element added to the stack.
void ArrayStack::print(ostream & out){
    for (int i = size-1; i>=0; --i){ // LIFO: last-in-first-out
        out << buf[i] << " ";
    }
}
ArrayStack::~ArrayStack(){ delete[] buf; } // destructor

// LISTNODE -----

void ListNode::print(ostream & out, ListNode * L){ out << L->data; }
void ListNode::delete_list(ListNode * L){
    ListNode * l = L;
    for (;l!=nullptr;){
        l = l->next;
        delete L; // L points to a index...
        L = l; // now we have L point to the next index.
    }
}

// LINKEDSTACK -----

// constructor
LinkedStack::LinkedStack()
    :Stack("LinkedStack"), head(nullptr)
{}

void LinkedStack::push(const string & word){ head = new ListNode(word, head); }
void LinkedStack::pop(){
    if (!is_empty()){
        ListNode * temp = head;
        head = head->next;
        delete temp;
    }
}
string LinkedStack::top(){
    if (!is_empty()){
        return head->data;
    }
    return "";
}
bool LinkedStack::is_empty(){
    return head == nullptr;
}
bool LinkedStack::is_full(){
    return false; // a LinkedStack can never be full because it grows dynamically...
}
void LinkedStack::print(ostream & out){
    for (ListNode *l = head; l != nullptr; l = l->next){
        ListNode::print(out, l);
        out << " ";
    }
}
LinkedStack::~LinkedStack(){
    ListNode::delete_list(head); // loops through using next and deletes everything in the LinkedStack
}


// ARRRAYQUEUE -----
// when the front == rear, the array is empty. 
ArrayQueue::ArrayQueue(int cap)
    :Queue("ArrayQueue"), capacity(cap + 1), front(0), rear(0), buf(new string[cap + 1])
{}

void ArrayQueue::enq(const string & word){
    if (!is_full()){
        buf[rear] = word;
        rear = (rear + 1) % capacity; // we use modulo here because the capacity could be less than 
    }
} 
void ArrayQueue::deq(){
    if (!is_empty()){
        front = (front + 1) % capacity;
    }
}
string ArrayQueue::next(){
    if (!is_empty()) return buf[front];
    return "";
}
bool ArrayQueue::is_empty(){
    return front == rear;
}
// front: points to the first element in the queue (index 0)
// rear: points to the last element in the queue (index 4)
// capacity: the maximum size of the queue (5)
bool ArrayQueue::is_full(){
    return front == (rear + 1) % capacity;
}
void ArrayQueue::print(ostream &out){
    for (int i = front; i != rear; i = (i + 1) % capacity){
        out << buf[i] << " ";
    }
}
ArrayQueue::~ArrayQueue(){ delete[] buf; }


// LINKEDQUEUE -----
LinkedQueue::LinkedQueue()
    :Queue("LinkedQueue"), head(nullptr), tail(nullptr)
{}

void LinkedQueue::enq(const string & word){
    ListNode * n = new ListNode(word, nullptr);
    if (head==nullptr){
        head = n;
        tail = n;
    }
    else{
        tail->next = n;
        tail = n;
    }
}
void LinkedQueue::deq(){
    if (!is_empty()){
        ListNode * temp = head;
        head = head->next;
        if (head == nullptr){ tail = nullptr; }
        delete temp;
    }
}
string LinkedQueue::next(){
    if (!is_empty()) return head->data;
    return "";
}
bool LinkedQueue::is_empty(){
    return head == nullptr;
}
bool LinkedQueue::is_full(){
    return false;
}
void LinkedQueue::print(ostream & out){
    for (ListNode * temp = head; temp != nullptr; temp = temp->next){
        ListNode::print(out, temp);
        out << " ";
    }
}
// this destructor has to be fixed...
LinkedQueue::~LinkedQueue(){
    ListNode::delete_list(head);
}

void error(string word, string msg)
{
    std::cout << "ERROR: " << word << " " << msg << endl;
}

void insert_all_words(int k, string file_name, Holder & L)
{
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k*NWORDS/10;
    t.start();
    for(string word; (in>>word)&& limit>0;--limit)
        L.insert(word);
    t.elapsedUserTime(eTime);
    in.close();
    std::cout<<"\t\tI = "<<eTime<<endl;
}

void remove_all_words(int k, string file_name, Holder & L)
{
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k*NWORDS/10;
    t.start();
    for(string word; (in>>word)&& limit>0;--limit)
        L.remove();
    t.elapsedUserTime(eTime);
    in.close();
    std::cout<<"\t\tI = "<<eTime<<endl;
}

void measure_holder(string file_name, Holder & L)
{
    std::cout<<L.name<<endl;
    for(int K=1; K<=10;++K)
    {
        std::cout<<"\tK = "<<K<<endl;
        insert_all_words(K,file_name,L);
        remove_all_words(K,file_name,L);
        if(!L.is_empty())
            error(L.name, "is not empty");
    }
}
void measure_holders(string input_file)
{
    ArrayStack AS(NWORDS);
    measure_holder(input_file, AS);
    LinkedStack LS;
    measure_holder(input_file, LS);
    ArrayQueue AQ(NWORDS);
    measure_holder(input_file, AQ);
    LinkedQueue LQ;
    measure_holder(input_file, LQ);
}
