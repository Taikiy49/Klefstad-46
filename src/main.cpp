#include "hashtable.h"

int main()
{
    measure_hashtables("src/random.txt");
}



#include <iostream>
#include <fstream>
using namespace std;
#include "hashtable.h"
#include "Timer.h"


void ListNode::print(ostream & out, ListNode * L)
{
    out<<L->data<<" ";
}

ListNode * ListNode::insert(string key, ListNode * L)
{
    L = new ListNode(key, L);
    return L;
}

ListNode * ListNode::find(string key, ListNode * L)
{
    for(ListNode*p=L;p!=nullptr;p=p->next)
    {
        if(p->data == key)
            return p;
    }
    return nullptr;
}

void ListNode::delete_list(ListNode * L)
{
    ListNode * l = L;
    for (;l!=nullptr;)
    {
        l = l->next;
        delete L;
        L = l;
    }
}

ListNode * ListNode::remove(string key, ListNode * L)
{
    ListNode * r = ListNode::find(key,L);

    if(r==L)
    {
        L = r->next;
        delete r;
        return L;
    }
    else
    {
        ListNode * prev = nullptr;
        for(ListNode * p= L; p!=nullptr; prev=p, p=p->next)
        {
            if(p==r)
            {
                prev->next=p->next;
                delete r;
                return L;
            }
        }
    
    }
    return L;
}

 int ListNode::length(ListNode * L)
 {
    int i=0;
    for(ListNode *p = L;p != nullptr;p = p->next)
        i++;

    return i;
 }

 /////////////////////////////////////////////////////////////////////

void HashTable::insert( const string & word)
{
    int h = hasher.hash(word,capacity);
    buf[h] = ListNode::insert(word, buf[h]);
}

bool HashTable::find( const string & word)
{
    int h = hasher.hash(word,capacity);
    return ListNode::find(word,buf[h]);
}

void HashTable::remove( const string & word)
{
    int h = hasher.hash(word, capacity);
    buf[h] = ListNode::remove(word,buf[h]);
}

bool HashTable::is_empty()
{
    for(size_t i = 0; i < capacity; ++i)
    {
        if (buf[i] != nullptr)
            return false;
    }
    return true;
}

bool HashTable::is_full()
{
    /*for(size_t i = 0; i < capacity; ++i)
    {
        if (buf[i] == nullptr)
            return false;
    }
    return true;
    */
   return false;
}

void HashTable::print(ostream & out)
{
    for (size_t i = 0; i < capacity; ++i)
    {
        for(ListNode*head = buf[i];head!=nullptr;head=head->next)
        {
            ListNode::print(out,head);
        }
    }
}

HashTable::~HashTable()
{
    for(size_t i = 0; i < capacity; ++i)
    {
        ListNode::delete_list(buf[i]);
    }
    delete[] buf;
}


size_t HashTable::number_of_entries()
{
    size_t count = 0;
    for (size_t i = 0; i < capacity; ++i)
    {
        if(buf[i]!=nullptr)
            count+=ListNode::length(buf[i]);
    }
    return count;
}

size_t HashTable::number_of_chains()
{
    /*size_t count = 0;
    for (int i = 0; i < capacity; ++i)
    {
        if (buf[i] != nullptr)
            count+=1;
    }
    return count;*/
    return capacity;
}

void HashTable::get_chain_lengths(vector<int> & v)
{
    for (size_t i = 0; i < capacity; ++i)
    {
        int len = ListNode::length(buf[i]);
        v.push_back(len);
    }
}


/////////////////////////////////////////////////////////////////////

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
    std::cout<<"\t\tI = "<<eTime<<endl;
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
    std::cout<<"\t\tI = "<<eTime<<endl;
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