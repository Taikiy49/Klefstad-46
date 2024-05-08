#include "hashtable.h"
#include <iostream>
#include "Timer.h"
#include <fstream>

using namespace std;

// LISTNODE -----
ListNode * ListNode::find(string key, ListNode * L){
    for (ListNode * p = L; p != nullptr; p=p->next)
        if (p->data == key) return p;
    return nullptr;
}

ListNode * ListNode::insert(string key, ListNode * L){
    return new ListNode(key, L);
}

// this one is a bit complicated. review this later...
ListNode* remove(string key, ListNode* L) {
    // if the ListNode is empty.
    if (L == nullptr)
        return nullptr;

    // if the node that we are trying to remove is the head of the list...
    if (L->data == key) {
        ListNode* temp = L->next;
        delete L;
        return temp;
    }

    ListNode* prev = L;
    ListNode* current = L->next;

    while (current != nullptr) {
        if (current->data == key) {
            prev->next = current->next;
            delete current;
            break;
        }
        prev = current;
        current = current->next;
    }

    return L;
}


int ListNode::length(ListNode * L){
    int i = 0;
    for (ListNode * p = L; p != nullptr; p=p->next) ++i
    return i;
}

void ListNode::delete_list(ListNode * L){
    ListNode * l = L;
    for(;l!=nullptr;){
        l = l->next;
        delete L;
        L = l;
    }
}

// HASHTABLE -----
void HashTable::insert(const string & word){}
bool HashTable::find(const string & word){}
void HashTable::remove(const string & word){}
bool HashTable::is_empty(){}
bool HashTable::is_full(){}
void HashTable::print(ostream & out){}
HashTable::~HashTable(){}

size_t HashTable::number_of_entries(){}
size_t HashTable::number_of_chains(){}
void HashTable::get_chain_lengths(vector<int> & v){}

//
void error(string word, string msg){
    std::cout << "ERROR: " << word << " " << msg << endl;
}

void insert_all_words( string file_name, HashTable & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for(string word; (in>>word)&& limit>0;--limit)
        L.insert(word);
    t.elapsedUserTime(eTime);
    in.close();
    std::cout<<"\t\tI = "<<eTime<<endl;

}
void find_all_words( string file_name, HashTable & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for(string word; (in>>word)&& limit>0;--limit)
        L.find(word);
    t.elapsedUserTime(eTime);
    in.close();
    std::cout<<"\t\tI = "<<eTime<<endl;
}

void remove_all_words( string file_name, HashTable & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for(string word; (in>>word)&& limit>0;--limit)
        L.remove(word);
    t.elapsedUserTime(eTime);
    in.close();
    std::cout<<"\t\tI = "<<eTime<<endl;
}

void measure_hashtable(string file_name, HashTable & L){
    cout << L.get_name() << endl;
    insert_all_words(file_name, L);

    vector<int> chain_lengths;
    L.get_chain_lengths(chain_lengths);
    Stats stats(L.get_name(), chain_lengths);
    stats.print(cout);

    find_all_words(file_name, L);
    remove_all_words(file_name, L);
    if(!(L.is_empty()))
        error(L.get_name(), "is not empty");
}
void measure_hashtables(string input_file){
    Hasher * H[]={
        new MultHasher{}
    };
    int S[] ={
        100
    };

    for (auto size: S)
        for(auto h :H)
        {
            HashTable ht(*h,size);
            measure_hashtable(input_file,ht);
        }
}