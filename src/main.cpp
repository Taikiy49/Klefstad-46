#include "holder.h"

int main()
{
    measure_holders("src/words.txt");
}

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "holder.h"
#include "Timer.h"

ArrayStack::ArrayStack(int cap)
    : Stack("ArrayStack"), capacity(cap), size(0), buf(new string[cap])
{
}

void ArrayStack::push(const string &word)
{
    if (!is_full())
        buf[size++] = word;
}

void ArrayStack::pop()
{
    if (!is_empty())
        --size;
}

string ArrayStack::top()
{
    if (!is_empty())
        return buf[size - 1];
    return "";
}

bool ArrayStack::is_empty()
{
    return size == 0;
}

bool ArrayStack::is_full()
{
    return size == capacity;
}

void ArrayStack::print(ostream &out)
{
    for (int i = size - 1; i >= 0; --i)
    {
        out << buf[i] << " ";
    }
}

ArrayStack::~ArrayStack()
{
    delete[] buf;
}

void ListNode::print(ostream &out, ListNode *L)
{
    out << L->data;
}

void ListNode::delete_list(ListNode *L)
{
    ListNode *l = L;
    for (; l != nullptr;)
    {
        l = l->next;
        delete L;
        L = l;
    }
}

LinkedStack::LinkedStack()
    : Stack("LinkedStack"), head(nullptr)
{
}

void LinkedStack::push(const string &word)
{
    head = new ListNode(word, head);
}

void LinkedStack::pop()
{
    if (!is_empty())
    {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

string LinkedStack::top()
{
    if (!is_empty())
    {
        return head->data;
    }
    return "";
}

bool LinkedStack::is_empty()
{
    return head == nullptr;
}

bool LinkedStack::is_full()
{
    return false;
}

void LinkedStack::print(ostream &out)
{
    for (ListNode *temp = head; temp != nullptr; temp = temp->next)
    {
        ListNode::print(out, temp);
        out << " ";
    }
}

LinkedStack::~LinkedStack()
{
    ListNode::delete_list(head);
}

ArrayQueue::ArrayQueue(int cap)
    : Queue("ArrayQueue"), capacity(cap + 1), front(0), rear(0), buf(new string[cap + 1])
{
}

void ArrayQueue::enq(const string &word)
{
    if (!is_full())
    {
        buf[rear] = word;
        rear = (rear + 1) % capacity;
    }
}

void ArrayQueue::deq()
{
    if (!is_empty())
    {
        front = (front + 1) % capacity;
    }
}
string ArrayQueue::next()
{
    if (!is_empty())
        return buf[front];
    return "";
}

bool ArrayQueue::is_empty()
{
    return front == rear;
}

bool ArrayQueue::is_full()
{
    return front == (rear + 1) % capacity;
}

void ArrayQueue::print(ostream &out)
{

    for (int i = front; i != rear; i = (i + 1) % capacity)
    {
        out << buf[i] << " ";
    }
}

ArrayQueue::~ArrayQueue()
{
    delete[] buf;
}

LinkedQueue::LinkedQueue()
    : Queue("LinkedQueue"), head(nullptr), tail(nullptr)
{
}

void LinkedQueue::enq(const string &word)
{
    ListNode *n = new ListNode(word, nullptr);
    if (head == nullptr)
    {
        head = n;
        tail = n;
    }
    else
    {
        tail->next = n;
        tail = n;
    }
}

void LinkedQueue::deq()
{
    if (!is_empty())
    {
        ListNode *temp = head;
        head = head->next;
        if (head == nullptr)
        {
            tail = nullptr;
        }
        delete temp;
    }
}
string LinkedQueue::next()
{
    if (!is_empty())
        return head->data;
    return "";
}

bool LinkedQueue::is_empty()
{
    return head == nullptr;
}

bool LinkedQueue::is_full()
{
    return false;
}

void LinkedQueue::print(ostream &out)
{
    for (ListNode *temp = head; temp != nullptr; temp = temp->next)
    {
        ListNode::print(out, temp);
        out << " ";
    }
}

LinkedQueue::~LinkedQueue()
{
    ListNode::delete_list(head);
}