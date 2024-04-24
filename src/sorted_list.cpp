#include <iostream>
#include <fstream>
#include "sorted_list.h"
#include "Timer.h"
using namespace std;

int SortedArrayList::find_index(const string & word){ // binary search!
    int low = 0;
    int high = size - 1; // consider the nullptr   
    while (low <= high){ 
        int mid = (low + high) / 2; // finding the mid will always be important for binary search!
        if (word == buf[mid]) return mid;
        else if (word < buf[mid]) high = mid - 1;
        else low = mid + 1;}
    return -1;}

void SortedArrayList::copy_down(int hole){
    auto _hole  = begin() + hole;
    std::copy_backward(_hole, end(), end() + 1);
    ++size;}

void SortedArrayList::copy_up(int hole){
    auto _hole = begin() + hole;
    std::copy(_hole + 1, end(), _hole);
    --size;
}

// constructor!
SortedArrayList::SortedArrayList(int cap):SortedList("ArrayList"), buf(new string[cap]), capacity(cap), size(0){}

void SortedArrayList::insert(const string & word){
    if (size==0){
        buf[0]=word;
        ++size; 
        return;
    }
    int i=0;
    for (auto e: *this){
        if (word < e) break;
        ++i;
    }
    copy_down(i);
    buf[i] = word;
}

bool SortedArrayList::find(const string & word){
    if (SortedArrayList::find_index(word)!= -1) return 1;
    else return 0;
}

void SortedArrayList::remove(const string & word){
    int i = SortedArrayList::find_index(word);
    if (i!=-1 && i>=0 && i<size) copy_up(i);
}

bool SortedArrayList::is_empty(){
    return size == 0;
}

bool SortedArrayList::is_full(){
    return size == capacity;
}

void SortedArrayList::print(ostream &out){
    for (auto e: *this)
        out << e << ' ';
}

SortedArrayList::~SortedArrayList(){
    delete[] buf;
}

//////////////////////////////////////////////

void ListNode::print(ostream &out, ListNode *L){
    out << L->data;
}

void ListNode::insert(const string & word, ListNode * L){
    ListNode *prev = nullptr;
    for (ListNode *p=L; p!=nullptr; prev=p, p=p->next){
        if (p->data>word){
            ListNode *n = new ListNode(word, p);
            if(prev == nullptr) L = n;
            else prev->next = n;
            return;
        }
        else if(p->data==word) return;
    }
    ListNode *n = new ListNode(word, nullptr);
    if (prev==nullptr) L=n;
    else prev->next = n;
    return;
}


ListNode * ListNode::find(const string &word, ListNode * L){
    for(ListNode *p = L; p!=nullptr; p=p->next){
        if (p->data == word){
            return p;
        }
    }
    return nullptr;
}

void ListNode::delete_list(ListNode *L){
    ListNode * l = L;
    for (;l!=nullptr;){
        l = l->next;
        delete L;
        L = l;
    }
}

void ListNode::remove(const string &word, ListNode * & L){
    ListNode *r = ListNode::find(word, L);
    if (r==L){
        L = r->next;
        delete r;
    }
    else{
        ListNode * prev = nullptr;
        for (ListNode * p = L; p!=nullptr; prev = p, p=p->next){
            if (p==r){
                prev->next=p->next;
                delete r;
                return;
            }
        }
    }
}

//////////////////////////////////////////

SortedLinkedList::SortedLinkedList():SortedList("LinkedList"), head(nullptr){}

void SortedLinkedList::insert(const string &word){
    ListNode::insert(word, head);
}

bool SortedLinkedList::find(const string &word){
    if (ListNode::find(word, head)) return -1;
    else return 0;
}

void SortedLinkedList::remove(const string &word){
    ListNode::remove(word, head);
}

bool SortedLinkedList::is_empty(){
    return head == nullptr;
}

bool SortedLinkedList::is_full(){
    return 0;
}

void SortedLinkedList::print(ostream &out){
    for (auto e: *this)
        out << e << ' ';
}

SortedLinkedList::~SortedLinkedList(){
    ListNode::delete_list(head);
}


//////////////////

ostream & operator<<(ostream &out, SortedList & L){
    L.print(out);
    return out;
}

void error(string word, string msg)
{
    std::cout << "ERROR: " << word << " " << msg << endl;
}

void insert_all_words(int k, string file_name, SortedList & L)
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
void find_all_words(int k, string file_name, SortedList & L)
{
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k*NWORDS/10;
    t.start();
    for(string word; (in>>word)&& limit>0;--limit)
        L.find(word);
    t.elapsedUserTime(eTime);
    in.close();
    std::cout<<"\t\tI = "<<eTime<<endl;
}

void remove_all_words(int k, string file_name, SortedList & L)
{
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k*NWORDS/10;
    t.start();
    for(string word; (in>>word)&& limit>0;--limit)
        L.remove(word);
    t.elapsedUserTime(eTime);
    in.close();
    std::cout<<"\t\tI = "<<eTime<<endl;
}

void measure_SortedList_methods(string file_name, SortedList & L)
{
    std::cout<<L.name<<endl;
    for(int K=1; K<=10;++K)
    {
        std::cout<<"\tK = "<<K<<endl;
        insert_all_words(K,file_name,L);
        find_all_words(K,file_name,L);
        remove_all_words(K,file_name,L);
        if(!L.is_empty())
            error(L.name, "is not empty");
    }
}
void measure_lists(string input_file)
{
    SortedArrayList UAL(NWORDS);
    measure_SortedList_methods(input_file, UAL);
    SortedLinkedList ULL;
    measure_SortedList_methods(input_file, ULL);
}