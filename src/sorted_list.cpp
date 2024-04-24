
#include <iostream>
#include <string>
#include <fstream>
#include "sorted_list.h"
#include "Timer.h"

using namespace std;

SortedArrayList::SortedArrayList(int cap)
    : SortedList("SortedArrayList"), capacity(cap), size(0), buf(new string[cap])
{
}

// Destructor
SortedArrayList::~SortedArrayList()
{
    delete[] buf;
}

// find_index helper
int SortedArrayList::find_index(const string &word)
{
    int low = 0;         // lower bound
    int high = size - 1; // upper bound
    int mid = (low + high) / 2;
    for (; low <= high; mid = (low + high) / 2)
    { // repeat until the search range is empty
        if (buf[mid] == word)
        {               // if the middle element is the target word
            return mid; // return its index
        }
        else if (buf[mid] < word)
        {                  // if the middle element is less than the target word
            low = mid + 1; // update the lower bound
        }
        else
        {                   // if the middle element is greater than the target word
            high = mid - 1; // update the upper bound
        }
    }
    return low; // return the index
}

// copy_up helper
void SortedArrayList::copy_up(int hole)
{
    for (int i = hole; i < size - 1; ++i)
    {
        buf[i] = buf[i + 1];
    }
    --size;
}

// copy_Down helper
void SortedArrayList::copy_down(int hole)
{
    for (int i = size; i > hole; --i)
    {
        buf[i] = buf[i - 1];
    }
    ++size;
}

bool SortedArrayList::find(const string &item)
{
    int i = find_index(item);
    return (i < size && buf[i] == item);
}

void SortedArrayList::insert(const string &item)
{
    if (is_full())
    {
        error("Opps! List is full", item);
        cout << "size:" << size << endl;
        cout << "capacity:" << capacity << endl;
        exit(0);
        return;
    }
    int i = find_index(item);
    copy_down(i);
    buf[i] = item;
}

void SortedArrayList::remove(const string &item)
{
    int i = find_index(item);
    if (buf[i] == item)
    {
        copy_up(i);
    }
}

bool SortedArrayList::is_empty()
{
    return size == 0;
}

bool SortedArrayList::is_full()
{
    return size == capacity;
}

// Use itegrator to print
void SortedArrayList::print(ostream &out)
{
    for (auto e : *this)
    {
        out << e << " ";
    }
}

ostream &operator<<(ostream &out, SortedList &L)
{
    L.print(out);
    return out;
}

// SLL
SortedLinkedList::SortedLinkedList() : SortedList("SortedLinkedList"), head(nullptr) {}

void SortedLinkedList::insert(const string &word)
{
    ListNode::insert(word, head);
}

bool SortedLinkedList::find(const string &word)
{
    return ListNode::find(word, head) != nullptr;
}

void SortedLinkedList::remove(const string &word)
{
    ListNode::remove(word, head);
}

bool SortedLinkedList::is_empty()
{
    return head == nullptr;
}

bool SortedLinkedList::is_full()
{
    return false;
}

void SortedLinkedList::print(ostream &out)
{
    for (auto e : *this)
    {
        out << e << " ";
    }
}

void ListNode::insert(const string &word, ListNode *&L)
{
    ListNode *prev = nullptr;

    for (ListNode *p = L; p != nullptr && word >= p->data; prev = p, p = p->next)
    {
        if (word == p->data)
        {
            return;
        }
    }
    if (prev == nullptr)
    {
        L = new ListNode(word, L);
    }
    else
    {
        prev->next = new ListNode(word, prev->next);
    }
}

ListNode *ListNode::find(const string &word, ListNode *L)
{
    while (L != nullptr && L->data != word)
    {
        L = L->next;
    }
    return L;
}

void ListNode::remove(const string &word, ListNode *&L)
{
    ListNode *prev = nullptr;
    ListNode *curr = L;
    while (curr != nullptr)
    {
        if (curr->data == word)
        {
            if (prev == nullptr)
            {
                L = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void ListNode::delete_list(ListNode *L)
{
    if (L != nullptr)
    {
        delete_list(L->next);
        delete L;
    }
}

SortedLinkedList::iterator SortedLinkedList::begin()
{
    return iterator(head);
}

SortedLinkedList::iterator SortedLinkedList::end()
{
    return iterator(nullptr);
}

SortedLinkedList::iterator::iterator(ListNode *const ptr) : current(ptr) {}

SortedLinkedList::iterator &SortedLinkedList::iterator::operator++()
{
    current = current->next;
    return *this;
}

SortedLinkedList::iterator SortedLinkedList::iterator::operator++(int)
{
    iterator temp = *this;
    ++(*this);
    return temp;
}

string &SortedLinkedList::iterator::operator*() const
{
    return current->data;
}

string *SortedLinkedList::iterator::operator->() const
{
    return &(current->data);
}

bool SortedLinkedList::iterator::operator==(iterator const &other) const
{
    return current == other.current;
}

bool SortedLinkedList::iterator::operator!=(iterator const &other) const
{
    return !(*this == other);
}

SortedLinkedList::~SortedLinkedList()
{
    ListNode::delete_list(head);
}

// Helper methods
void error(string word, string msg)
{
    cerr << "Error: " << msg << " - " << word << endl;
}

bool insert_all_words(int k, string file_name, SortedList &L)
{
    Timer t;
    double eTime;
    ifstream infile(file_name);
    if (!infile)
    {
        error("Unable to open input file", file_name);
        return false;
    }
    string word;
    int limit = k * NWORDS / 10;
    t.start();
    for (int i = 0; i < limit && infile >> word; ++i)
    {
        L.insert(word);
    }
    t.elapsedUserTime(eTime);
    infile.close();
    cout << "\t\tI = " << eTime << endl;
    return true;
}

void find_all_words(int k, string file_name, SortedList &L)
{
    Timer t;
    double eTime;
    ifstream infile(file_name);
    if (!infile)
    {
        error("Unable to open input file", file_name);
        return;
    }
    string word;
    int limit = k * NWORDS / 10;
    t.start();
    for (int i = 0; i < limit; ++i)
    {
        infile >> word;
        L.find(word);
    }
    t.elapsedUserTime(eTime);
    infile.close();
    cout << "\t\tF = " << eTime << endl;
}

void remove_all_words(int k, string file_name, SortedList &L)
{
    Timer t;
    double eTime;
    ifstream infile(file_name);
    if (!infile)
    {
        error("Unable to open input file", file_name);
        return;
    }
    string word;
    int limit = k * NWORDS / 10;
    t.start();
    for (int i = 0; i < limit; ++i)
    {
        infile >> word;
        L.remove(word);
    }
    t.elapsedUserTime(eTime);
    infile.close();
    cout << "\t\tR = " << eTime << endl;
}

void measure_SortedList_methods(string file_name, SortedList &L)
{
    cout << L.name << endl;
    for (int K = 1; K <= 10; ++K)
    {
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        find_all_words(K, file_name, L);
        remove_all_words(K, file_name, L);
        if (!L.is_empty())
        {
            error(L.name, "is not empty");
            exit(0);
        }
    }
}

void measure_lists(string input_file)
{
    SortedArrayList SAL(NWORDS);
    measure_SortedList_methods(input_file, SAL);

    SortedLinkedList SLL;
    measure_SortedList_methods(input_file, SLL);
}
