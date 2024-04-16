#include <iostream>
#include "unordered_list.h"
#include "Timer.h"
using namespace std;

// this section is for the UnordererdArrayList!
int UnorderedArrayList::find_index(const string & word){
    for (int i=0; i < size; ++i)
        if (buf[i] == word) return i;
    return -1;
}

UnorderedArrayList::UnorderedArrayList(int max_len):
UnorderedList("ArrayList"), buf(new string[max_len]), capacity(max_len), size(0) {}

void UnorderedArrayList::insert(const string &word){
    buf[size++] = word;}

bool UnorderedArrayList::find(const string &word){
    if (UnorderedArrayList::find_index(word) != -1)
        return 1;
    else return 0;
}

void UnorderedArrayList::remove(const string & word){
    int i = UnorderedArrayList::find_index(word);
    if (i!=-1){
        buf[i] = buf[size-1];
        size--;
    }
}

bool UnorderedArrayList::is_empty(){
    return size == 0;}

bool UnorderedArrayList::is_full(){
    return size == capacity;}

// void UnorderedArrayList::erase(){
// }

void UnorderedArrayList::print(ostream &out){
    for (int i=0; i < size; ++i)
        out << buf[i];
    out << endl;
}

UnorderedArrayList::~UnorderedArrayList(){
    delete[] buf;}


// this section is for ListNodes!

void ListNode::print(ostream &out, ListNode *L){
    out << L->data;}

ListNode *ListNode::find(const string &word, ListNode *L){

    for (;L!=nullptr;L=L->next)
        if (L->data == word)
            return L;
    return nullptr;
}

void ListNode::delete_list(ListNode *L){   
    ListNode *current = L;
    while (current != nullptr){
        ListNode *nextNode = current->next;
        delete current;
        current = nextNode;
    }

void ListNode::remove(const string &word, ListNode * & L){
    ListNode * r = ListNode::find(word, L);
    if (r==L){
        L = r->next;
        delete r;}
    else{
        ListNode *current = L;
        L = L->next;
        for(;L!=nullptr;L=L->next){
            if (L==r){
                current->next=L->next;
                delete L;
                break;
            }
            current = current->next;
        }
    }
}

// this section is for the UnorderedLinkedList
UnorderedLinkedList::UnorderedLinkedList():UnorderedList("LinkedList"), head(nullptr){}
void UnorderedLinkedList::insert(const string &word){
    head = new ListNode(word, head);}

bool UnorderedLinkedList::find(const string &word){
    if (ListNode::find(word, head))
        return 1;
    else return 0;
}

void UnorderedLinkedList::remove(const string &word){
    ListNode *r = ListNode:;find(word, head);
    if (r==head){
        head = r->next;
        delete r;
    }
    else{
        ListNode *current = head;
        ListNode *after = head->next;
        for (;after != nullptr; after = after->next){
            if (after==r){
                current->next = after->next;
                delete after;
                break;
            }
            current = current->next;
        }
    }
}