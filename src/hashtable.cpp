#include "hashtable.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include "Timer.h"
#include "stats.h"
#include <string>

using namespace std;


// ListNode methods
ListNode * ListNode::find(string key, ListNode * L) {
    while (L != nullptr && L->data != key) {
        L = L->next; // move to the next node
    }
    return L; // return the node containing the key
}

ListNode * ListNode::insert(string key, ListNode * L) {
    //if (find(key, L) == nullptr) {
        L = new ListNode(key, L); // create a new node with the key and add it to the list
    //}
    return L;
}

ListNode * ListNode::remove(string key, ListNode * L) {
    if (L == nullptr) {
        return nullptr; // key not found
    } else if (L->data == key) {
        ListNode* temp = L->next;// store the next node in a temporary variable
        delete L;
        return temp;
    } else {
        L->next = remove(key, L->next);// recursively call remove on the next node
        return L;// return the current node
    }
}

void ListNode::print(ostream & out, ListNode * L) {
    while (L != nullptr) {
        out << L->data << " ";
        L = L->next;
    }
}

int ListNode::length(ListNode * L) {
    int count = 0;// initialize a counter 
    while (L != nullptr) { // while the current node is not null
        count++;// increment the counter
        L = L->next;// move to the next node
    }
    return count;
}

void ListNode::delete_list(ListNode * L) {
    if (L != nullptr) {
        delete_list(L->next);
        delete L;
    }
}

// HashTable methods
void HashTable::insert(const string & word
) {
    size_t index = hasher.hash(word,capacity);
    buf[index] = ListNode::insert(word, buf[index]);
}

bool HashTable::find(const string & word) {
    size_t index = hasher.hash(word,capacity);
    return ListNode::find(word, buf[index]);
}

void HashTable::remove(const string & word) {
    size_t index = hasher.hash(word,capacity);
    buf[index] = ListNode::remove(word, buf[index]);
}

bool HashTable::is_empty() {
    for (size_t i = 0; i < capacity; ++i) {
        if (buf[i] != nullptr) {// if not empty
            return false;
        }
    }
    return true;
}

bool HashTable::is_full() {
    return false; // always return false, since the hash table is never full
}

void HashTable::print(ostream & out) {
    for (size_t i = 0; i < capacity; ++i) {
        ListNode::print(out, buf[i]);
    }
}

//destructor
HashTable::~HashTable() {
    for (size_t i = 0; i < capacity; ++i) {
        ListNode::delete_list(buf[i]);
    }
    delete[] buf;
}

//Returns the total number of entries in the hash table.
size_t HashTable::number_of_entries() {
    size_t count = 0;// initialize a counter
    for (size_t i = 0; i < capacity; i++) {
        // add the length of the list at the current index to the counter
        count += ListNode::length(buf[i]);
    }
    return count;// return the total number of entries
}

size_t HashTable::number_of_chains() {
    return capacity;
}

void HashTable::get_chain_lengths(vector<int> & v) {
    for (size_t i = 0; i < capacity; i++) {
        // push the length of each chain onto the vector
        v.push_back(ListNode::length(buf[i]));
    }
}


void error(string word, string msg)
{
    std::cout << "ERROR: " << word << " " << msg << endl;
}

void insert_all_words( string file_name, HashTable & L)
{
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
void find_all_words( string file_name, HashTable & L)
{
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for(string word; (in>>word)&& limit>0;--limit)
        L.find(word);
    t.elapsedUserTime(eTime);
    in.close();
    std::cout<<"\t\tF = "<<eTime<<endl;
}

void remove_all_words( string file_name, HashTable & L)
{
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for(string word; (in>>word)&& limit>0;--limit)
        L.remove(word);
    t.elapsedUserTime(eTime);
    in.close();
    std::cout<<"\t\tR = "<<eTime<<endl;
}

void measure_hashtable(string file_name, HashTable & L)
{
    /*std::cout<<L.name<<endl;
    for(int K=1; K<=10;++K)
    {
        std::cout<<"\tK = "<<K<<endl;
        insert_all_words(K,file_name,L);
        find_all_words(K,file_name,L);
        remove_all_words(K,file_name,L);
        if(!L.is_empty())
            error("hi","is not empty");
    }*/
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
void measure_hashtables(string input_file)
{
    Hasher * H[]={
        new MyHasher{}
        // new MultHasher{}
    };
    int S[] ={
        1,
    };

    for (auto size: S)
        for(auto h :H)
        {
            HashTable ht(*h,size);
            measure_hashtable(input_file,ht);
        }



}